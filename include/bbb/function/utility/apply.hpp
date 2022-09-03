/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/utility/apply.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp.hpp>

namespace bbb {
    namespace function {
        namespace utility {
            namespace detail {
                template <typename return_value_t, typename ... arguments, std::size_t ... indicies>
                return_value_t apply(std::function<return_value_t(arguments ...)> f, std::tuple<arguments ...> t, index_sequence<indicies ...>) {
                    return f(std::get<indicies>(t) ...);
                };
            };

            template <typename return_value_t, typename ... arguments>
            return_value_t apply(std::function<return_value_t(arguments ...)> f, std::tuple<arguments ...> t) {
                return detail::apply(f, t, index_sequence_for<arguments ...>());
            }
            template <typename function_t, typename ... arguments>
            typename function_traits<function_t>::result_type apply(function_t f, std::tuple<arguments ...> t) {
                return detail::apply(function_traits<function_t>::cast(f), t, make_index_sequence<function_traits<function_t>::arity>());
            }
        };
    };
};
