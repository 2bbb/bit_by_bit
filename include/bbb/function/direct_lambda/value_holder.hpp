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

#include <bbb/function/direct_lambda/direct_function.hpp>

#include <bbb/core.hpp>

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

#define def_unary_op(op, name)\
                constexpr auto operator op() const\
                -> direct_function<op_type::name, direct_function>\
                { return {*this}; }

                def_unary_op(!, unary_not);
                def_unary_op(~, unary_bit_not);
                def_unary_op(+, unary_plus);
                def_unary_op(-, unary_minus);
                def_unary_op(&, address);
                def_unary_op(*, dereference);
#undef def_unary_op

                template <typename index_t>
                constexpr auto operator[](const index_t &index) const
                -> direct_function<op_type::subscript, direct_function, index_t>
                { return {std::tuple<direct_function, index_t>(*this, index)}; }

                // TODO implement member pointer
                template <typename obj, typename result, typename ... arguments>
                constexpr auto operator->*(result(obj::*meth)(arguments ...)) const
                -> direct_function<op_type::member_pointer, direct_function, result(obj::*)(arguments ...)>
                { return {std::tuple<direct_function, result(obj::*)(arguments ...)>(*this, meth)}; }
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

#define def_unary_op(op, name)\
                constexpr auto operator op() const\
                -> direct_function<op_type::name, direct_function>\
                { return {*this}; }

                def_unary_op(!, unary_not);
                def_unary_op(~, unary_bit_not);
                def_unary_op(+, unary_plus);
                def_unary_op(-, unary_minus);
                def_unary_op(&, address);
                def_unary_op(*, dereference);
#undef def_unary_op

                template <typename index_t>
                constexpr auto operator[](const index_t &index) const
                -> direct_function<op_type::subscript, direct_function, index_t>
                { return {std::tuple<direct_function, index_t>(*this, index)}; }

                // TODO implement member pointer
                template <typename obj, typename result, typename ... arguments>
                constexpr auto operator->*(result(obj::*meth)(arguments ...)) const
                -> direct_function<op_type::member_pointer, direct_function, result(obj::*)(arguments ...)>
                { return {std::tuple<direct_function, result(obj::*)(arguments ...)>(*this, meth)}; }
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

#define def_unary_op(op, name)\
                constexpr auto operator op() const\
                -> direct_function<op_type::name, direct_function>\
                { return {*this}; }

                def_unary_op(!, unary_not);
                def_unary_op(~, unary_bit_not);
                def_unary_op(+, unary_plus);
                def_unary_op(-, unary_minus);
                def_unary_op(&, address);
                def_unary_op(*, dereference);
#undef def_unary_op

                template <typename index_t>
                constexpr auto operator[](const index_t &index) const
                -> direct_function<op_type::subscript, direct_function, index_t>
                { return {std::tuple<direct_function, index_t>(*this, index)}; }

                // TODO implement member pointer
                template <typename obj, typename result, typename ... arguments>
                constexpr auto operator->*(result(obj::*meth)(arguments ...)) const
                -> direct_function<op_type::member_pointer, direct_function, result(obj::*)(arguments ...)>
                { return {std::tuple<direct_function, result(obj::*)(arguments ...)>(*this, meth)}; }
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
        };
        using direct_lambda::operator""_c;
    };
};

using bbb::function::operator""_c;
