/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/traits/function_traits.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <type_traits>
#include <tuple>
#include <functional>

#include <bbb/core/basic.hpp>
#include <bbb/core/traits/type_traits.hpp>

namespace bbb {
    namespace function_info {
        namespace detail {
            template <typename ret, typename ... arguments>
            struct function_traits {
                static constexpr std::size_t arity = sizeof...(arguments);
                using result_type = ret;
                using arguments_types_tuple = std::tuple<arguments ...>;
                template <std::size_t index>
                using argument_type = type_at_t<index, arguments ...>;
                using function_type = std::function<ret(arguments ...)>;
                template <typename function_t>
                static constexpr function_type cast(function_t f) {
                    return static_cast<function_type>(f);
                }
            };
        };

        template <typename T>
        struct function_traits : public function_traits<decltype(&T::operator())> {};

        template <typename class_type, typename ret, typename ... arguments>
        struct function_traits<ret(class_type::*)(arguments ...) const>
            : detail::function_traits<ret, arguments ...> {};

        template <typename class_type, typename ret, typename ... arguments>
        struct function_traits<ret(class_type::*)(arguments ...)>
            : detail::function_traits<ret, arguments ...> {};

        template <typename ret, typename ... arguments>
        struct function_traits<ret(*)(arguments ...)>
            : detail::function_traits<ret, arguments ...> {};

        template <typename ret, typename ... arguments>
        struct function_traits<ret(arguments ...)>
            : detail::function_traits<ret, arguments ...> {};

        template <typename ret, typename ... arguments>
        struct function_traits<std::function<ret(arguments ...)>>
            : detail::function_traits<ret, arguments ...> {};

        template<typename T>
        using result_type = typename function_traits<T>::result_type;

        template<typename T>
        using arguments_types_tuple = typename function_traits<T>::arguments_types_tuple;

        template<typename T, std::size_t index>
        using argument_type = typename function_traits<T>::template argument_type<index>;

        template<typename T>
        struct arity {
            static constexpr std::size_t value = function_traits<T>::arity;
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

        template <typename callback_type, typename ... arg_types>
        struct detect_result_type {
            using type = decltype(std::declval<callback_type>()(std::declval<arg_types>() ...));
        };

        template <typename Fn, typename Type>
        constexpr bool is_argument_same_to() {
            return std::is_same<
                typename std::remove_reference<typename function_traits<Fn>::template argument_type<0>>::type,
                Type
            >::value;
        }
        
        template <typename A, typename B>
        constexpr bool composable() {
            return std::is_same<
                typename function_traits<A>::result_type,
                typename std::remove_reference<typename function_traits<B>::template argument_type<0>>::type
            >::value;
        }
    };
    using namespace function_info;
};
