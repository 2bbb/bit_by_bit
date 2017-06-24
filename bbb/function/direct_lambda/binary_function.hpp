/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/binary_function.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/function/direct_lambda/constants.hpp>
#include <bbb/function/direct_lambda/utility.hpp>
#include <bbb/function/direct_lambda/base_class.hpp>
#include <bbb/function/direct_lambda/direct_function.hpp>
#include <bbb/function/direct_lambda/value_holder.hpp>
#include <bbb/function/direct_lambda/placeholder.hpp>
#include <bbb/function/direct_lambda/type_traits.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            template <typename function_type, typename lhs_type, typename rhs_type>
            struct eval<op_type::binary_func_apply, function_type, lhs_type, rhs_type> {
                template <typename ... arguments>
                constexpr auto evaluate(const std::tuple<function_type, lhs_type, rhs_type> &holder,
                                        arguments && ... args) const
                -> typename function_type::template result_t<
                    decltype(std::get<1>(holder)(std::forward<arguments>(args) ...)),
                    decltype(std::get<2>(holder)(std::forward<arguments>(args) ...))
                >
                {
                    return (std::get<0>(holder))(
                        std::get<1>(holder)(std::forward<arguments>(args) ...),
                        std::get<2>(holder)(std::forward<arguments>(args) ...)
                    );
                }
            };

#define def_std_binary_function(name)\
            namespace detail {\
                struct name##_function {\
                    template <typename lhs_type, typename rhs_type>\
                    using result_t = decltype(std::name(std::declval<lhs_type>(), std::declval<rhs_type>()));\
                    \
                    template <typename lhs_type, typename rhs_type>\
                    constexpr result_t<lhs_type, rhs_type> operator()(const lhs_type &x, const rhs_type &y) const { return std::name(x, y); }\
                };\
            };\
            template <\
                typename lhs_type,\
                typename rhs_type,\
                typename _ = type_enable_if_t<conjunction<\
                    is_direct_function<lhs_type>,\
                    is_direct_function<rhs_type>\
                >>\
            >\
            direct_function<op_type::binary_func_apply, detail::name##_function, lhs_type, rhs_type> name(const lhs_type &x, const rhs_type &y) {\
                return {std::tuple<detail::name##_function, lhs_type, rhs_type>({}, x, y)};\
            }
        };
    };
};