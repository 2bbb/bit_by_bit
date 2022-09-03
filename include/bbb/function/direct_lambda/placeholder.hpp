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
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/function/direct_lambda/constants.hpp>
#include <bbb/function/direct_lambda/base_class.hpp>
#include <bbb/function/direct_lambda/direct_function.hpp>
#include <bbb/function/direct_lambda/utility.hpp>

#include <bbb/core.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            namespace detail {
                template <too_long n>
                struct index_type {
                    static constexpr too_long value = n;
                };
            };

            template <too_long n>
            using placeholder = direct_function<op_type::placeholder, detail::index_type<n>>;

            template <too_long n>
            struct eval<op_type::placeholder, detail::index_type<n>> {
                template <typename ... arguments>
                constexpr auto evaluate(const std::tuple<detail::index_type<n>> &, arguments && ... args) const
                -> type_at_t<n - 1, arguments ...>
                { return value_at<n - 1, arguments ...>(std::forward<arguments>(args) ...); }
            };

            template <char ... chars>
            constexpr placeholder<detail::to_number<chars ...>::value> operator""_() {
                static_assert(0 < detail::to_number<chars ...>::value, "0_ is not allowed");
                return {};
            };

            template <typename type>
            struct is_placeholder {
                static constexpr too_long value = std::is_placeholder<type>::value;
            };

            template <too_long n>
            struct is_placeholder<placeholder<n>> {
                static constexpr too_long value = n;
            };

            template <too_long n>
            struct is_direct_function<placeholder<n>> : std::true_type {};
        };

        using direct_lambda::operator""_;
    };
};
