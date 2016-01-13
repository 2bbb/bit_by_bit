/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * main.cpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#include "bit_by_bit.hpp"
#include "simple_test.hpp"

bbb_test_declaretion(test);
void reusable_array_test();
void byte_array_test();
bbb_test_declaretion(iterator_delegation);
void iterator_test();
bbb_test_declaretion(container_delegation)
void multithread_test();
void enumerate_test();
void logger_test();

int main(int argc, char *argv[]) {
    bbb_test(test);
    reusable_array_test();
    byte_array_test();
    bbb_test(iterator_delegation);
    bbb_test(container_delegation);
    multithread_test();
    enumerate_test();
}

bbb_test_begin_definition(test)
bbb_assert(true);
bbb_test_end_definition(test)

#pragma mark reusable_array_test

#include <cassert>
#include <iostream>

struct particle {
    int life_time;
    int age;
    int name;

    particle() {}
    particle(int life_time, int name)
        : life_time(life_time)
        , name(name)
        , age(0) {}

    void init(int life_time, int name) {
        this->life_time = life_time;
        this->name = name;
        this->age = 0;
    }

    bool update() {
        return ++age < life_time;
    }

    void print() const {
        std::cout << name << ", " << (life_time - age) << std::endl;
    }
};

constexpr int loop_num(1);
constexpr int elem_num(10);

void reusable_array_test() {
    bbb::random::set_seed_mt(0);
    auto a = bbb::random::mt();
    bbb::random::set_seed_mt(0);
    auto b = bbb::random::mt();
    bbb::random::set_seed_mt(1);
    auto c = bbb::random::mt();
    assert(a == b);
    assert(a != c);

    bbb::stop_watch watch;
    watch.start();

    {
        bbb::random::set_seed_mt(0);
        bbb::reusable_array<particle, elem_num> f;
        watch.rap();

        for(int k = 0; k++ < loop_num;) {
            do f.init(bbb::random::mt() % 100, f.current_size()); while(f.has_space());
            while(f.current_size()) {
                f.update();
            }
        }

        watch.rap();
        std::cout << "time: " << watch.getLastRapNanoseconds() << std::endl;
    }

    {
        bbb::random::set_seed_mt(0);
        bbb::shared_vector<particle> f;
        watch.rap();

        for(int k = 0; k++ < loop_num;) {
            for(; f.size() < elem_num; f.push_back(std::shared_ptr<particle>(new particle(rand() % 100, f.size()))));
            auto wrapper = bbb::make_reverse(f);
            while(f.size()) for(auto e : wrapper) if(!e->update()) {
                e = f.back();
                f.pop_back();
            }
        }

        watch.rap();
        std::cout << "time: " << watch.getLastRapNanoseconds() << std::endl;
    }
}

void byte_array_test() {
    bbb::byte_array<int> barr{0x7FFFFFFF};
    for(auto i = 0; i < barr.size(); i++) {
        std::cout << (int)barr[i] << std::endl;
    }
    for(auto &b : barr) {
        std::cout << (int)b << std::endl;
    }
};

void multithread_test() {
    const std::size_t num = 4;
    std::size_t sum = 0;
    bool is_run = true;
    bbb::stop_watch watch;
    watch.start();
    bbb::multithread::manager manager(num, [&sum, &is_run](std::size_t index, std::mutex &mutex) {
        while(is_run) {
            if(mutex.try_lock()) {
                sum++;
                mutex.unlock();
            }
            bbb::sleep_nanoseconds(50);
        }
    });

    while(is_run) {
        bbb::sleep_milliseconds(10);
        auto lock(manager.lock_guard());
        if(100000 < sum) {
            is_run = false;
            manager.join();
        }
    }
    watch.rap();
    std::cout << "time: " << watch.getLastRapMilliseconds() << std::endl;
}

void enumerate_test() {
    {
        std::vector<int> vec;
        bbb::for_each(bbb::range(10, 2), [&vec](int x) { vec.push_back(x); });
        bbb::for_each(vec, [](int &x) { x *= 2; });

        for(auto &v : bbb::enumerate(vec)) {
            std::cout << v.index() << ", " << v.value() << std::endl;
            v.value() *= 2;
        }
        for(auto v : bbb::enumerate(vec)) {
            std::cout << v.index() << ", " << v.value() << std::endl;
        }
    }
    std::cout << std::endl;
    {
        std::vector<int> cvec{1, 2, 3};
        for(auto v : bbb::enumerate(cvec)) {
            std::cout << v.index() << ", " << v.value() << std::endl;
        }
    }
    std::cout << std::endl;
    {
        std::vector<const std::string> svec{"a", "hoge", "foo"};
//        for (const auto &v : bbb::enumerate(svec)) {
//            std::cout << v.index() << ", " << v.value() << std::endl;
//        }
//        for (const auto &v : bbb::enumerate(svec)) {
//            std::cout << v.index() << ", " << v.value() << std::endl;
//        }
    }
}

#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <map>
#include <string>

bbb_test_begin_prepare(iterator_delegation)
struct vectroid
    : bbb::iterator_delegation<std::vector<int>> {
    std::vector<int> body;

    vectroid() : delegation(body) { };
};

struct mappoid : bbb::iterator_delegation<std::map<int, int>> {
    std::map<int, int> body;

    mappoid() : delegation(body) { };
};

struct introid : bbb::iterator_delegation<int> {
    int body;

    introid() : delegation(body) { };
};
bbb_test_end_prepare(iterator_delegation)

bbb_test_begin_definition(iterator_delegation)

bbb_assert(bbb::iteratable_class_traits<std::vector<int>>::has_iterator);
bbb_assert(bbb::iteratable_class_traits<std::vector<int>>::has_reverse_iterator);
bbb_assert(bbb::iteratable_class_traits<std::map<int, int>>::has_iterator);
bbb_assert(bbb::iteratable_class_traits<std::string>::has_iterator);
bbb_assert(!bbb::iteratable_class_traits<int>::has_iterator);
bbb_assert(bbb::iteratable_class_traits<bbb::iterator_delegation<std::vector<int>>>::has_iterator);

bbb_assert(bbb::iteratable_class_traits<std::vector<int>>::has_insert);
bbb_assert(bbb::iteratable_class_traits<std::vector<int>>::has_push_back);
bbb_assert(!bbb::iteratable_class_traits<std::vector<int>>::has_push_front);

bbb_assert(bbb::iteratable_class_traits<std::deque<int>>::has_insert);
bbb_assert(bbb::iteratable_class_traits<std::deque<int>>::has_push_back);
bbb_assert(bbb::iteratable_class_traits<std::deque<int>>::has_push_front);

bbb_assert(bbb::iteratable_class_traits<std::list<int>>::has_insert);
bbb_assert(bbb::iteratable_class_traits<std::list<int>>::has_push_back);
bbb_assert(bbb::iteratable_class_traits<std::list<int>>::has_push_front);

bbb_assert(!bbb::iteratable_class_traits<std::queue<int>>::has_insert);
bbb_assert(!bbb::iteratable_class_traits<std::queue<int>>::has_push_back);
bbb_assert(!bbb::iteratable_class_traits<std::queue<int>>::has_push_front);

bbb_assert(!bbb::iteratable_class_traits<int>::has_insert);
bbb_assert(!bbb::iteratable_class_traits<int>::has_push_back);
bbb_assert(!bbb::iteratable_class_traits<int>::has_push_front);

vectroid v;
v.body.push_back(-1);
v.body.push_back(-2);
v.body.push_back(-3);

std::vector<int> src{1, 2, 3, 4};
std::copy(src.begin(), src.end(), std::back_inserter(v));
std::copy(src.begin(), src.end(), std::inserter(v, v.begin()));

{
    auto it = std::begin(v);
    bbb_assert(*it++ == 1);
    bbb_assert(*it++ == 2);
    bbb_assert(*it++ == 3);
    bbb_assert(*it++ == 4);
    bbb_assert(*it++ == -1);
    bbb_assert(*it++ == -2);
    bbb_assert(*it++ == -3);
    bbb_assert(*it++ == 1);
    bbb_assert(*it++ == 2);
    bbb_assert(*it++ == 3);
    bbb_assert(*it++ == 4);
}
mappoid m;
m.body.insert(std::make_pair(2, 3));
m.body.insert(std::make_pair(6, 7));
m.body.insert(std::make_pair(4, 5));
m.body.insert(std::make_pair(8, 9));
{
    auto it = std::begin(m);
    bbb_assert(it->first == 2 && (it++)->second == 3);
    bbb_assert(it->first == 4 && (it++)->second == 5);
    bbb_assert(it->first == 6 && (it++)->second == 7);
    bbb_assert(it->first == 8 && (it++)->second == 9);
}
introid i;
//	for(auto &it : i) {} // Error: delegated type doesn't provide iterator

bbb_test_end_definition(iterator_delegation)

bbb_test_begin_prepare(container_delegation)

struct int_arrayoid : bbb::container_delegation<std::array<int, 8>> {
    std::array<int, 8> v;
    int_arrayoid() : delegation(v) {}
};

struct int_vectroid : bbb::container_delegation<std::vector<int>> {
    std::vector<int> v;
    int_vectroid() : delegation(v) {}
};

bbb_test_end_prepare(container_delegation)

bbb_test_begin_definition(container_delegation)
    {
        int_arrayoid::value_type t;
        int_arrayoid v;
        bbb_assert(v.size() == 8);
        bbb_assert(!v.empty());
    }

    {
        int_vectroid::value_type t;
        int_vectroid v;
        bbb_assert(v.size() == 0);
        v.push_back(1);
        v.push_back(2);
        bbb_assert(v.size() == 2);
        bbb_assert(v[0] == 1);
        bbb_assert(v[1] == 2);
        v.emplace_back(3);
        bbb_assert(v.size() == 3);
        bbb_assert(v[2] == 3);
    }
bbb_test_end_definition(container_delegation)

void logger_test() {
    bbb::logger::trace() << "begin logger_test";
    bbb::logger::info("foo") << "foo" << "bar";
    bbb::logger::trace() << "end logger_test";
}
