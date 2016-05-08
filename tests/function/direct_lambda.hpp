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
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/misc/simple_test.hpp>
#include <bbb/misc/demangled_type.hpp>

#include <bbb/function/direct_lambda.hpp>

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
bbb_test_end_definition(direct_lambda)
