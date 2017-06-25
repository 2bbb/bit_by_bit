/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/direct_function.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/function/direct_lambda/constants.hpp>
#include <bbb/function/direct_lambda/base_class.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            template <op_type op, typename ... holders>
            struct direct_function {
                std::tuple<holders ...> holder;
                direct_function() {};
                direct_function(const direct_function &df)
                : holder(df.holder) {};
                direct_function(direct_function &&df)
                : holder(std::move(df.holder)) {};
                direct_function(const std::tuple<holders ...> &holder)
                : holder(holder) {};
                direct_function(std::tuple<holders ...> &&holder)
                : holder(std::move(holder)) {};

                template <typename ... arguments>
                constexpr auto operator()(arguments && ... args) const
                -> decltype(eval<op, holders ...>().evaluate(holder, std::forward<arguments>(args) ...))
                {
                    return eval<op, holders ...>().evaluate(holder, std::forward<arguments>(args) ...);
                }

#include <bbb/function/direct_lambda/direct_function.inc>
            };

            template <typename>
            struct is_direct_function : std::false_type {};
            template <op_type op, typename ... holders>
            struct is_direct_function<direct_function<op, holders ...>> : std::true_type {};

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

            #define f_address(arg) &arg
            def_unary_op_eval(f_address, address);
            #undef f_address

            #define f_dereference(arg) (*arg)
            def_unary_op_eval(f_dereference, dereference);
            #undef f_dereference

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
#undef def_unary_function_eval

            template <
                typename function_type,
                typename object_type,
                typename result_type,
                typename ... arguments_type
            >
            struct eval<
                op_type::member_pointer,
                function_type,
                result_type(object_type::*)(arguments_type ...) const
            > {
                template <typename ... arguments>
                constexpr result_type evaluate(
                    const std::tuple<
                        function_type,
                        result_type(object_type::*)(arguments_type ...) const
                    > &holder,
                    arguments && ... args
                ) const {
                    return (
                        (std::get<0>(holder))(std::forward<arguments>(args) ...)
                        ->*
                        (std::get<1>(holder))
                    )();
                }
            };

        };
    };
};