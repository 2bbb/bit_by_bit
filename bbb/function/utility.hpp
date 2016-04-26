/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/utility.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

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
                return detail::apply(f, t, get_type<index_sequence_for<arguments ...>>());
            }
            template <typename function_t, typename ... arguments>
            typename function_info<function_t>::result_type apply(function_t f, std::tuple<arguments ...> t) {
                return detail::apply(static_cast<typename function_info<function_t>::function_type>(f), t, get_type<make_index_sequence<function_info<function_t>::arity>>());
            }
        };
        using namespace utility;
    };
    using namespace function;
}