/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * tests/function/lambda_symbol.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

#include <bbb/misc/simple_test.hpp>

#include <bbb/function/lambda_symbol.hpp>

bbb_test_begin_prepare(lambda_symbol)
    int g(std::function<int(const int &)> f) {
        return f(4);
    }
bbb_test_end_prepare(lambda_symbol)

bbb_test_begin_definition(lambda_symbol)
    bbb_use_lambda_symbol(_);

    bbb_assert(g(2 + _) == 6);
    bbb_assert((2 << _)(3) == 2 << 3);
    bbb_assert((2 + _)(2) == 4);
    bbb_assert((_ == 2)(2));
    bbb_assert(!(_ == 2)(3));
    bbb_assert((_ == "x")("x"));
    bbb_assert(!(_ == "x")("y"));

    std::function<bool(int)> f = (2 == _);
    bbb_assert(f(2));

    std::vector<int> vec = {{1, 2, 3, 4}};
    bbb_assert((_[vec])(0) == 1);
    bbb_assert((_([](int x) { return x + 1; }))(4) == 5);

    int sum = 0;
    std::for_each(vec.begin(), vec.end(), sum += _);
    bbb_assert(sum == 10);

    std::vector<int> filtered;
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(filtered), 2 < _);
    bbb_assert(filtered[0] == 3);
    bbb_assert(filtered[1] == 4);
bbb_test_end_definition(lambda_symbol)
