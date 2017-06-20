/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/type_traits.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/function/direct_lambda/base_class.hpp>
#include <bbb/function/direct_lambda/direct_function.hpp>
#include <bbb/function/direct_lambda/placeholder.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            template <typename>
            struct is_direct_function
            : std::false_type {};
            template <op_type op, typename ... holders>
            struct is_direct_function<direct_function<op, holders ...>>
            : std::true_type {};

            template <typename value_type>
            struct wrap_value_type {
                using type = conditional_t<
                    is_direct_function<value_type>::value,
                    value_type,
                    value_holder<value_type>
                >;
            };
            template <typename value_type>
            struct wrap_const_value_type {
                using type = conditional_t<
                    is_direct_function<value_type>::value,
                    value_type,
                    const_value_holder<value_type>
                >;
            };

            template <typename type>
            struct is_direct_lambdable
            : disjunction<is_direct_function<type>, is_placeholder<type>> {};
        };
    };
};
