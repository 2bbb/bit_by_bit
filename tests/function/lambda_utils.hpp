/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * lambda_utils.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include "function/lambda_utils.hpp"
#include "misc/simple_test.hpp"
#include <iostream>

bbb_test_begin_prepare(lambda)
    struct Object {
        int get() {
            return 42;
        }
    };

    int mult_2(int x) {
        return 2 * x;
    }
bbb_test_end_prepare(lambda)

bbb_test_begin_definition(lambda)
//        Object o;
//        auto f = bbb::curry::extraction(&o, &Object::get);
//        assert(f == 42 && "lambda: f() == 42");
//
//        auto g = bbb::curry::bind(mult_2, &Object::get, 4);
//        assert(g(&o) == 84 && "lambda: g(&o) == 84");
        bbb::apply([](int x) { std::cout << "apply :" << x << std::endl; }, std::make_tuple(1));
        std::cout << "apply: " << bbb::apply(
            [](int x, float y) { return x + y; },
            std::make_tuple(1, 1.2f)
        );
bbb_test_end_definition(lambda)
