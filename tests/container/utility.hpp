/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * tests/container/utility.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/misc/simple_test.hpp>

#include <bbb/container/utility.hpp>

bbb_test_begin_definition(enumerate)
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
bbb_test_end_definition(enumerate)

