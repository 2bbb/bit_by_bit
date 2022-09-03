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

#include <bbb/function/direct_lambda/base_class.hpp>
#include <bbb/function/direct_lambda/constants.hpp>

#include <bbb/core.hpp>

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

            // TODO implement member pointer
            #define f_member_pointer(f, x) (f->*x)
            def_unary_function_eval(f_member_pointer, member_pointer);
            #undef f_member_pointer
#undef def_unary_function_eval

        };
    };
};