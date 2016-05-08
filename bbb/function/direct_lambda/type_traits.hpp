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
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/function/direct_lambda/base_class.hpp>
#include <bbb/function/direct_lambda/placeholder.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            template <typename>
            struct is_function { static constexpr bool value = false; };
            template <op_type op, typename ... holders>
            struct is_function<function<op, holders ...>> { static constexpr bool value = true; };

            template <typename>
            struct is_placeholder { static constexpr bool value = false; };
            template <too_long n>
            struct is_placeholder<placeholder<n>> { static constexpr bool value = true; };

            template <typename type>
            struct is_functional_element {
                static constexpr bool value = is_function<type>::value || is_placeholder<type>::value;
            };

            template <typename value_type>
            struct wrap_value_type {
                using type = conditional<
                    is_functional_element<value_type>::value,
                    value_type,
                    value_holder<value_type>
                >;
            };

            template <typename value_type>
            struct wrap_const_value_type {
                using type = conditional<
                    is_functional_element<value_type>::value,
                    value_type,
                    const_value_holder<value_type>
                >;
            };
        };
    };
};
