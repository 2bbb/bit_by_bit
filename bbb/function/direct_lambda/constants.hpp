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
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <tuple>
#include <bbb/core.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            using too_long = unsigned long long;

            enum class op_type : std::uint_fast8_t {
                placeholder, value_holder, const_value_holder,
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
                unary_func_apply
            };
        };
    };
};
