/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/function_info.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <type_traits>
#include <tuple>
#include <functional>

#include <bbb/core/type.hpp>

namespace bbb {
    namespace tmp {
        namespace function_traits {
            namespace detail {
                template <typename ret, typename ... arguments>
                struct function_info {
                    static constexpr std::size_t arity = sizeof...(arguments);
                    using result_type = ret;
                    using arguments_types_tuple = std::tuple<arguments ...>;
                    template <std::size_t index>
                    using argument_type = type_at<index, arguments ...>;
                    using function_type = std::function<ret(arguments ...)>;
                };
            };

            template <typename T>
            struct function_info : public function_info<decltype(&T::operator())> {};

            template <typename class_type, typename ret, typename ... arguments>
            struct function_info<ret(class_type::*)(arguments ...) const>
                : detail::function_info<ret, arguments ...> {};

            template <typename class_type, typename ret, typename ... arguments>
            struct function_info<ret(class_type::*)(arguments ...)>
                : detail::function_info<ret, arguments ...> {};

            template <typename ret, typename ... arguments>
            struct function_info<ret(*)(arguments ...)>
                : detail::function_info<ret, arguments ...> {};

            template <typename ret, typename ... arguments>
            struct function_info<ret(arguments ...)>
                : detail::function_info<ret, arguments ...> {};

            template <typename ret, typename ... arguments>
            struct function_info<std::function<ret(arguments ...)>>
                : detail::function_info<ret, arguments ...> {};

            template<typename T>
            using result_type = typename function_info<T>::result_type;

            template<typename T>
            using arguments_types_tuple = typename function_info<T>::arguments_types_tuple;

            template<typename T, std::size_t index>
            using argument_type = typename function_info<T>::template argument_type<index>;

            template<typename T>
            struct arity {
                static constexpr std::size_t value = function_info<T>::arity;
            };

            template <typename patient>
            struct has_call_operator {
                template <typename inner_patient, decltype(&inner_patient::operator())> struct checker {};
                template <typename inner_patient> static std::true_type  check(checker<inner_patient, &inner_patient::operator()> *);
                template <typename>               static std::false_type check(...);
                using type = decltype(check<patient>(nullptr));
                static constexpr bool value = type::value;
            };

            template <typename patient>
            constexpr bool is_callable(const patient &) {
                return std::is_function<patient>::value || has_call_operator<patient>::value;
            };
        };
        using namespace function_traits;
    };
};
