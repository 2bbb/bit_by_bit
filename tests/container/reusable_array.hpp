/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * tests/container/reusable_array.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/misc/simple_test.hpp>

#include <cassert>
#include <iostream>

#include <bbb/container/reusable_array.hpp>

bbb_test_begin_prepare(reusable_array)
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
bbb_test_end_prepare(reusable_array)

bbb_test_begin_definition(reusable_array)

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

bbb_test_end_definition(reusable_array)
