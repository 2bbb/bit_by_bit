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
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            template <typename value_t>
            struct value_holder : function<op_type::value_holder, value_t &> {
                value_holder(value_t &v)
                    : function<op_type::value_holder, value_t &>({v}) {};
            };

            template <typename value_t>
            struct eval<op_type::value_holder, value_t &> {
                template <typename ... arguments>
                constexpr value_t &evaluate(const std::tuple<value_t &> &holder,
                                            arguments && ... args) const
                { return std::get<0>(holder); }
            };

            template <typename value_t>
            struct const_value_holder : function<op_type::const_value_holder, const value_t &> {
                const_value_holder(const value_t &v)
                    : function<op_type::const_value_holder, const value_t &>({v}) {};
            };

            template <typename value_t>
            struct eval<op_type::const_value_holder, const value_t &> {
                template <typename ... arguments>
                constexpr const value_t &evaluate(const std::tuple<const value_t &> &holder,
                                            arguments && ... args) const
                { return std::get<0>(holder); }
            };
        };
    };
};
