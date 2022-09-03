/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/unary_function.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/function/direct_lambda/constants.hpp>
#include <bbb/function/direct_lambda/utility.hpp>
#include <bbb/function/direct_lambda/base_class.hpp>
#include <bbb/function/direct_lambda/direct_function.hpp>
#include <bbb/function/direct_lambda/value_holder.hpp>
#include <bbb/function/direct_lambda/placeholder.hpp>
#include <bbb/function/direct_lambda/type_traits.hpp>

#include <bbb/core.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            template <typename function_type, typename argument_type>
            struct eval<op_type::unary_func_apply, function_type, argument_type> {
                template <typename ... arguments>
                constexpr auto evaluate(const std::tuple<function_type, argument_type> &holder, arguments && ... args) const
                -> typename function_type::template result_t<decltype(((std::get<1>(holder))(std::forward<arguments>(args) ...)))>
                {
                    return (std::get<0>(holder))((std::get<1>(holder))(std::forward<arguments>(args) ...));
                }
            };

#define def_std_unary_function(name)\
            namespace detail {\
                struct name##_function {\
                    template <typename type>\
                    using result_t = decltype(std::name(std::declval<type>()));\
                    \
                    template <typename type>\
                    constexpr result_t<type> operator()(const type &x) const { return std::name(x); }\
                };\
            };\
            template <typename argument_type, typename _ = enable_if_t<is_direct_function<argument_type>::value>>\
            direct_function<op_type::unary_func_apply, detail::name##_function, argument_type> name(const argument_type &arg) {\
                return {std::tuple<detail::name##_function, argument_type>({}, arg)};\
            }
        };
    };
};
