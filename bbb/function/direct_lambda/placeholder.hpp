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
#include <bbb/function/direct_lambda/base_class.hpp>
#include <bbb/function/direct_lambda/function.hpp>
#include <bbb/function/direct_lambda/utility.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            namespace detail {
                template<too_long n> struct index_type {
                    static constexpr too_long value = n;
                };
            };

            template <too_long n>
            using placeholder = function<op_type::placeholder, detail::index_type<n>>;

            template <too_long n>
            struct eval<op_type::placeholder, detail::index_type<n>> {
                template <typename ... arguments>
                constexpr auto evaluate(const std::tuple<detail::index_type<n>> &, arguments && ... args) const
                -> type_at<n - 1, arguments ...>
                { return value_at<n - 1, arguments ...>(std::forward<arguments>(args) ...); }
            };

            template <char ... chars>
            constexpr placeholder<detail::to_number<chars ...>::value> operator""_() {
                static_assert(0 < detail::to_number<chars ...>::value, "0_ is not allowed");
                return {};
            };
        };
    };
};