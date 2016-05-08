/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/placeholder.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/function/direct_lambda/constants.hpp>
#include <bbb/function/direct_lambda/utility.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            template <too_long n>
            struct placeholder {
                template <typename ... arguments>
                constexpr type_at<n - 1, arguments ...> operator()(arguments && ... args) const
                {
                    return value_at<n - 1, arguments ...>(std::forward<arguments>(args) ...);
                }
            };

            template <char ... chars>
            constexpr placeholder<detail::to_number<chars ...>::value> operator""_() {
                static_assert(0 < detail::to_number<chars ...>::value, "0_ is not allowed");
                return {};
            };
        };
    };
};
