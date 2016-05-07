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

    std::function<bool(int)> f = (2 == _);
    std::cout << g(2 + _) << std::endl;
    std::cout << (2 << _)(3) << std::endl;
    std::cout << (2 + _)(2) << std::endl;
    std::cout << (_ == 2)(2) << std::endl;
    std::cout << (_ == "x")("x") << std::endl;

    std::vector<int> vec = {{1, 2, 3, 4}};
    std::cout << (_[vec])(0) << std::endl;
    std::cout << (_([](int x) { return x; }))(4) << std::endl;

    int sum = 0;
    std::for_each(vec.begin(), vec.end(), sum += _);
    std::cout << sum << std::endl;

    std::vector<int> filtered;
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(filtered), 2 < _);
    std::for_each(filtered.begin(), filtered.end(), [](int x) { std::cout << x << std::endl; });
bbb_test_end_definition(lambda_symbol)
