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

#include <bbb/function/direct_lambda/base_class.hpp>
#include <bbb/function/direct_lambda/direct_function.hpp>
#include <bbb/function/direct_lambda/placeholder.hpp>

#include <bbb/core.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            template <typename value_type>
            struct wrap_value_type {
                using type = conditional_t<
                    is_direct_function<value_type>::value,
                    value_type,
                    value_holder<value_type>
                >;
            };
            template <typename value_type>
            using wrap_value_type_t = get_type<wrap_value_type<value_type>>;

            template <typename value_type>
            struct wrap_const_value_type {
                using type = conditional_t<
                    is_direct_function<value_type>::value,
                    value_type,
                    const_value_holder<value_type>
                >;
            };
            template <typename value_type>
            using wrap_const_value_type_t = get_type<wrap_const_value_type<value_type>>;

            template <typename value_type>
            struct wrap_type
                : embedding<wrap_const_value_type_t<value_type>> {};
            template <typename value_type>
            struct wrap_type<value_type &>
                : embedding<wrap_value_type_t<value_type>> {};
            template <typename value_type>
            struct wrap_type<const value_type &>
                : embedding<wrap_const_value_type_t<value_type>> {};
            
            template <typename value_type>
            using wrap_type_t = get_type<wrap_type<value_type>>;

            template <typename value_type>
            auto wrap(value_type && v)
                -> type_enable_if_t<
                    is_direct_function<value_type>,
                    value_type &&
                >
            {
                return v;
            }
            template <typename value_type>
            auto wrap(value_type & v)
                -> type_enable_if_t<
                    is_direct_function<value_type>,
                    value_type &
                >
            {
                return v;
            }
            template <typename value_type>
            auto wrap(value_type & v)
                -> type_enable_if_t<
                    negation<is_direct_function<value_type>>,
                    value_holder<value_type>
                >
            {
                return {v};
            }
            template <typename value_type>
            auto wrap(value_type && v)
                -> type_enable_if_t<
                    negation<is_direct_function<value_type>>,
                    const_value_holder<value_type>
                >
            {
                return {std::forward<value_type>(v)};
            }
        };
    };
};
