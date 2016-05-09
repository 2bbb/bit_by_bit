/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/function.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/function/direct_lambda/base_class.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            template <op_type op, typename ... holders>
            struct function {
                std::tuple<holders ...> holder;

                template <typename ... arguments>
                constexpr auto operator()(arguments && ... args) const
                -> decltype((eval<op, holders ...>()).evaluate(holder, std::forward<arguments>(args) ...))
                {
                    return (eval<op, holders ...>()).evaluate(holder, std::forward<arguments>(args) ...);
                }

                constexpr auto operator!() const
                -> function<op_type::unary_not, function>
                { return {*this}; }

                constexpr auto operator~() const
                -> function<op_type::unary_bit_not, function>
                { return {*this}; }

                constexpr auto operator+() const
                -> function<op_type::unary_plus, function>
                { return {*this}; }

                constexpr auto operator-() const
                -> function<op_type::unary_minus, function>
                { return {*this}; }

                template <typename index_t>
                constexpr auto operator[](const index_t &index) const
                -> function<op_type::subscript, function, index_t>
                { return {std::tuple<function, index_t>(*this, index)}; }
            };

#define def_unary_op_eval(f, name)\
            template <typename function_type>\
            struct eval<op_type::name, function_type> {\
                template <typename ... arguments>\
                constexpr auto evaluate(const std::tuple<function_type> &holder, arguments && ... args) const\
                -> decltype(f((std::get<0>(holder))(std::forward<arguments>(args) ...)))\
                { return f((std::get<0>(holder))(std::forward<arguments>(args) ...)); }\
            };

            #define f_unary_not(arg) !arg
            def_unary_op_eval(f_unary_not, unary_not);
            #undef f_unary_not

            #define f_unary_bit_not(arg) ~arg
            def_unary_op_eval(f_unary_bit_not, unary_bit_not);
            #undef f_unary_bit_not

            #define f_unary_plus(arg) +arg
            def_unary_op_eval(f_unary_plus, unary_plus);
            #undef f_unary_plus

            #define f_unary_minus(arg) -arg
            def_unary_op_eval(f_unary_minus, unary_minus);
            #undef f_unary_minus
#undef def_unary_op_eval

#define def_unary_function_eval(f, name)\
            template <typename function_type, typename argument_type>\
            struct eval<op_type::name, function_type, argument_type> {\
                template <typename ... arguments>\
                constexpr auto evaluate(const std::tuple<function_type, argument_type> &holder, arguments && ... args) const\
                -> decltype(f((std::get<0>(holder))(std::forward<arguments>(args) ...), (std::get<1>(holder))(std::forward<arguments>(args) ...)))\
                { return f((std::get<0>(holder))(std::forward<arguments>(args) ...), (std::get<1>(holder))(std::forward<arguments>(args) ...)); }\
            };

            #define f_subscript(f, x) f[x]
            def_unary_function_eval(f_subscript, subscript);
            #undef f_subscript
        };
    };
};
