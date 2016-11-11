/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/utility.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            namespace detail {
                constexpr too_long pow10(too_long digit) { return digit == 0 ? 1 : (10 * pow10(digit - 1)); }
                constexpr too_long char_to_i(char c) { return (c - '0'); }

                template <char c, char ... chars>
                struct to_number {
                    static constexpr too_long value = char_to_i(c) * pow10(sizeof...(chars)) + to_number<chars ...>::value;
                };

                template <char c>
                struct to_number<c> {
                    static constexpr too_long value = char_to_i(c);
                };
            };
        };
    };
};
