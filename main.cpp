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

void reusable_array_test();
void byte_array_test();
void multithread_test(size_t num);
void range_test();
void logger_test();

int main(int argc, char *argv[]) {
    reusable_array_test();
    byte_array_test();
    multithread_test(4);
    range_test();
}

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
};

void multithread_test(size_t num) {
    size_t sum = 0;
    bool is_run = true;
    bbb::stop_watch watch;
    watch.start();
    bbb::multithread::manager manager(num, [&sum, &is_run](size_t index, std::mutex &mutex) {
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

void range_test() {
    {
        std::vector<int> vec;
        bbb::for_each(bbb::range(10, 2), [&vec](int x) { vec.push_back(x); });
        bbb::for_each(vec, [](int &x) { x *= 2; });

        for(auto v : bbb::enumerate(vec)) {
            std::cout << v.index << ", " << v.value << std::endl;
            v.value *= 2;
        }
        for(auto v : bbb::enumerate(vec)) {
            std::cout << v.index << ", " << v.value << std::endl;
        }
    }

    {
        const std::vector<int> cvec{1, 2, 3};
        for(auto v : bbb::enumerate(cvec)) {
            std::cout << v.index << ", " << v.value << std::endl;
        }
    }
    std::cout << std::endl;

    std::vector<std::string> svec{"a", "hoge", "foo"};
    for(auto &v : bbb::enumerate(svec)) {
        std::cout << v.index << ", " << v.value << std::endl;
    }
    for(const auto &v : bbb::enumerate(svec)) {
        std::cout << v.index << ", " << v.value << std::endl;
    }
}

void logger_test() {
//    bbb::logger::add_file_logger("foo", "/Users/2bit/foo.txt");
    bbb::logger::trace() << "begin logger_test";
    bbb::logger::info("foo") << "foo" << "bar";
    bbb::logger::trace() << "end logger_test";
}