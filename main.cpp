#include "src/bit_by_bit.hpp"
#include <stdlib.h>
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
};

constexpr int loop_num(10000);
constexpr int elem_num(1000);

int main(int argc, char *argv[]) {
    bbb::stop_watch watch;
    watch.start();

    {
        srand(0);
        bbb::reusable_array<particle, elem_num> f;
        watch.rap();

        for(int k = 0; k++ < loop_num;) {
            do f.init(rand() % 100, f.current_size()); while(f.has_space());
            while(f.current_size()) f.update();
        }

        watch.rap();
        std::cout << "time: " << watch.getLastRapNanoseconds() << std::endl;
    }

    {
        srand(0);
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