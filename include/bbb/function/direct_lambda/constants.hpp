/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/constants.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

#include <tuple>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            using too_long = unsigned long long;

            enum class op_type : std::uint_fast8_t {
                placeholder, value_holder, const_value_holder, cast_holder,
                unary_not, unary_bit_not, unary_plus, unary_minus,
                address, dereference,
                subscript,
                member_pointer, // TODO implement member pointer
                eq, neq,
                lt, lte, gt, gte,
                add, sub, mul, div, mod,
                land, lor,
                band, bor, bxor,
                lshift, rshift,
                unary_func_apply,
                binary_func_apply,
                binded_function,
                binded_function_apply
            };
        };
    };
};
