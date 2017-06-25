/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/value_holder.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/function/direct_lambda/direct_function.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            template <typename value_t>
            struct direct_function<op_type::value_holder, value_t &> {
                std::tuple<const value_t &> holder;
                template <typename ... arguments>
                constexpr auto operator()(arguments && ... args) const
                -> decltype(eval<op_type::value_holder, value_t &>().evaluate(holder, std::forward<arguments>(args) ...))
                {
                    return eval<op_type::value_holder, value_t &>().evaluate(holder, std::forward<arguments>(args) ...);
                }

#include <bbb/function/direct_lambda/direct_function.inc>
            };
            template <typename value_t>
            struct direct_function<op_type::const_value_holder, value_t> {
                std::tuple<value_t> holder;
                template <typename ... arguments>
                constexpr auto operator()(arguments && ... args) const
                -> decltype(eval<op_type::const_value_holder, value_t>().evaluate(holder, std::forward<arguments>(args) ...))
                {
                    return eval<op_type::const_value_holder, value_t>().evaluate(holder, std::forward<arguments>(args) ...);
                }

#include <bbb/function/direct_lambda/direct_function.inc>
            };

            template <typename value_t>
            struct direct_function<op_type::const_value_holder, const value_t &> {
                std::tuple<value_t> holder;
                template <typename ... arguments>
                constexpr auto operator()(arguments && ... args) const
                -> decltype(eval<op_type::const_value_holder, const value_t &>().evaluate(holder, std::forward<arguments>(args) ...))
                {
                    return eval<op_type::const_value_holder, const value_t &>().evaluate(holder, std::forward<arguments>(args) ...);
                }
#include <bbb/function/direct_lambda/direct_function.inc>
            };

            template <typename value_t>
            struct value_holder : direct_function<op_type::value_holder, value_t &> {
                value_holder(value_t &v)
                    : direct_function<op_type::value_holder, value_t &>({v}) {};
            };

            template <typename value_t>
            struct is_value_holder : std::false_type {};
            template <typename value_t>
            struct is_value_holder<value_holder<value_t>> : std::true_type {};
            template <typename value_type>
            struct is_direct_function<value_holder<value_type>> : std::true_type {};

            template <typename value_t>
            struct eval<op_type::value_holder, value_t &> {
                template <typename ... arguments>
                constexpr value_t &evaluate(const std::tuple<value_t &> &holder,
                                            arguments && ... args) const
                { return std::get<0>(holder); }
            };

            template <typename value_t, bool b = is_number<value_t>::value>
            struct const_value_holder : direct_function<op_type::const_value_holder, const value_t &> {
                constexpr const_value_holder(const value_t &v)
                    : direct_function<op_type::const_value_holder, const value_t &>({v}) {};
            };

            template <typename value_t>
            struct const_value_holder<value_t, true> : direct_function<op_type::const_value_holder, value_t> {
                constexpr const_value_holder(value_t v)
                    : direct_function<op_type::const_value_holder, value_t>({v}) {};
            };

            template <typename value_t>
            struct is_const_value_holder : std::false_type {};
            template <typename value_t>
            struct is_const_value_holder<const_value_holder<value_t>> : std::true_type {};
            template <typename value_type>
            struct is_direct_function<const_value_holder<value_type>> : std::true_type {};

            template <typename value_t>
            struct eval<op_type::const_value_holder, const value_t &> {
                template <typename ... arguments>
                constexpr const value_t &evaluate(const std::tuple<const value_t &> &holder,
                                                  arguments && ... args) const
                { return std::get<0>(holder); }
            };
            template <typename value_t>
            struct eval<op_type::const_value_holder, value_t> {
                template <typename ... arguments>
                constexpr const value_t &evaluate(const std::tuple<value_t> &holder,
                                                  arguments && ... args) const
                { return std::get<0>(holder); }
            };

            constexpr const_value_holder<long double> operator""_c(long double value) {
                return {value};
            }
            constexpr const_value_holder<unsigned long long> operator""_c(unsigned long long value) {
                return {value};
            }

            template <typename value_type>
            constexpr const_value_holder<value_type> val(value_type &&value) {
                return {std::forward<value_type>(value)};
            }
            template <typename value_type>
            constexpr value_holder<value_type> ref(value_type &value) {
                return {value};
            }
        };
        using direct_lambda::operator""_c;
        using direct_lambda::val;
        using direct_lambda::ref;
    };
};

using bbb::function::operator""_c;
