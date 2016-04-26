/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/type/utility.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <type_traits>
#include <tuple>
#include <functional>

#include <bbb/core/constants.hpp>

namespace bbb {
    template <typename T>
    using get_type = typename T::type;

    template <bool b, typename T = void>
    using enable_if = get_type<std::enable_if<b, T>>;

    template <bool b, typename T, typename F>
    using conditional = get_type<std::conditional<b, T, F>>;

    template <typename T, typename U>
    constexpr bool is_same() { return std::is_same<T, U>::value; };

    template <typename T>
    constexpr bool is_const() {
        return std::is_const<T>::value;
    }

    template <typename T>
    constexpr bool is_number() {
        return std::is_arithmetic<T>::value;
    }

    template <typename T>
    constexpr bool is_integer() {
        return std::is_integral<T>::value;
    }

    template <typename T>
    constexpr bool is_float() {
        return std::is_floating_point<T>::value;
    }

    template <typename T>
    using remove_const_reference_if_number = get_type<std::conditional<
        is_number<T>(),
        get_type<std::remove_reference<
            get_type<std::remove_const<T>>
        >>,
        T
    >>;

    template <typename T>
    using add_const_reference_if_not_number = get_type<std::conditional<
        !is_number<T>(),
        get_type<std::add_const<
            get_type<std::add_lvalue_reference<T>>
        >>,
        T
    >>;

    template <std::size_t index, typename ... arguments>
    using type_at = get_type<std::tuple_element<index, std::tuple<arguments ...>>>;
};