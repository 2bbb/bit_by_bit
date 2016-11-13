/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/traits/type_traits.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <type_traits>
#include <tuple>

#include <bbb/core/constants.hpp>
#include <bbb/core/basic.hpp>

namespace bbb {
    using std::enable_if;

    template <bool b, typename T = void>
    using enable_if_t = get_type<enable_if<b, T>>;

    using std::conditional;

    template <bool b, typename T, typename F>
    using conditional_t = get_type<conditional<b, T, F>>;

    using std::is_same;

#if bbb_is_cpp14
    template <typename T, typename U>
    constexpr bool is_same_v = is_same<T, U>::value;
#endif

    template <typename T, typename U>
    constexpr bool is_same_f() { return is_same<T, U>::value; };

    using std::is_const;

#if bbb_is_cpp14
    template <typename T>
    constexpr bool is_const_v = is_const<T>::value;
#endif

    template <typename T>
    constexpr bool is_const_f() {
        return is_const<T>::value;
    }

    template <typename T>
    using is_number = std::is_arithmetic<T>;

#if bbb_is_cpp14
    template <typename T>
    constexpr bool is_numver_v = is_number<T>::value;
#endif

    template <typename T>
    constexpr bool is_number_f() {
        return is_number<T>::value;
    }

    template <typename T>
    using is_integer = std::is_integral<T>;

#if bbb_is_cpp14
    template <typename T>
    constexpr bool is_integer_v = is_integer<T>::value;
#endif

    template <typename T>
    constexpr bool is_integer_f() {
        return is_integer<T>::value;
    }

    template <typename T>
    using is_float = std::is_floating_point<T>;

#if bbb_is_cpp14
    template <typename T>
    constexpr bool is_float_v = is_float<T>::value;
#endif

    template <typename T>
    constexpr bool is_float_f() {
        return is_float<T>::value;
    }

    template <typename T>
    using remove_const_reference_if_number = get_type<std::conditional<
        is_number_f<T>(),
        get_type<std::remove_reference<
            get_type<std::remove_const<T>>
        >>,
        T
    >>;

    template <typename T>
    using add_const_reference_if_not_number = get_type<std::conditional<
        !is_number_f<T>(),
        get_type<std::add_const<
            get_type<std::add_lvalue_reference<T>>
        >>,
        T
    >>;

    template <std::size_t index, typename ... arguments>
    using type_at = get_type<std::tuple_element<index, std::tuple<arguments ...>>>;

    template <std::size_t index, typename ... arguments>
    type_at<index, arguments ...> value_at(arguments && ... args) {
        return std::get<index>(std::tuple<arguments ...>(std::forward<arguments>(args) ...));
    };

    template <bool condition, template <typename ...> class t, template <typename ...> class f>
    struct template_conditional {
        template <typename ... arguments>
        using type = get_type<std::conditional<condition, t<arguments ...>, f<arguments ...>>>;
    };
};
