/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * tests/function/direct_lambda.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/misc/simple_test.hpp>

#include <vector>

#include <bbb/function/direct_lambda.hpp>

bbb_test_begin_prepare(direct_lambda)
    struct simple_struct {
        int get_int() const { return 4; }
        float get_float() const { return 4.0f; }
    };
bbb_test_end_prepare(direct_lambda);

bbb_test_begin_definition(direct_lambda)
    bbb_assert((2 * (1_ * 1_) - (2_ / 3_))(1, 2, 3) == 2 * 1 * 1 - 2 / 3);
    bbb_assert((2 * (1_ * 1_) - (2_ / 3_))(1, 2, 3.0f) == 2 * 1 * 1 - 2 / 3.0f);
    bbb_assert((1_ * 0.3f * 2_ + 3_ * 4_)(2, 2, 3, 4));
    bbb_assert((1_ + 2_)("abc", std::string("def")) == "abcdef");
    bbb_assert((1_ == 2_ * 3_)(6, 2, 3));
    bbb_assert((1_ == 2_ * 3_)(6, 2, 4) == false);
    bbb_assert((sin(1_))(2.0 * M_PI) == std::sin(2.0 * M_PI));
    bbb_assert((cos(1_ + 2 * 2_))(1.0, 2.3f) == std::cos(1.0 + 2 * 2.3f));
    bbb_assert(abs(1_)(-4.3) == std::abs(-4.3));

    bbb_assert((!1_)(false) == true);
    bbb_assert((!1_)(true) == false);
    bbb_assert((!(1_ || 2_))(true, false) == false);

    bbb_assert((~1_)(2) == ~2);

    bbb_assert((+1_)(false) == +false);
    bbb_assert((-1_)(true) == -true);

    {
        std::vector<int> vec = {1, 2, 3};
        auto f_subscript = 1_[2_];
        bbb_assert(f_subscript(vec, 0) == vec[0]);
        bbb_assert(f_subscript(vec, 1) == vec[1]);
        bbb_assert(f_subscript(vec, 2) == vec[2]);
    }

    {
        int arr[] = {1, 2, 3};
        auto f_subscript = 1_[2_];
        bbb_assert(f_subscript(arr, 0) == arr[0]);
        bbb_assert(f_subscript(arr, 1) == arr[1]);
        bbb_assert(f_subscript(arr, 2) == arr[2]);
        bbb_assert(f_subscript(0, arr) == arr[0]);
        bbb_assert(f_subscript(1, arr) == arr[1]);
        bbb_assert(f_subscript(2, arr) == arr[2]);
    }

        // TODO implement member pointer
//    simple_struct p;
//    bbb_assert(((1_->*2_)(p, &simple_struct::get_int))() == 4);
//    bbb_assert(((1_->*2_)(p, &simple_struct::get_float))() == 4.0f);
bbb_test_end_definition(direct_lambda)
