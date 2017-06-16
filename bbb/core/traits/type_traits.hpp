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
    /**
     * enable_if
     */
    using std::enable_if;

    template <bool b, typename T = void>
    using enable_if_t = get_type<enable_if<b, T>>;

    /**
     * conditional
     */
    using std::conditional;

    template <bool b, typename T, typename F>
    using conditional_t = get_type<conditional<b, T, F>>;

    /**
     * is_null_pointer
     */
#if bbb_is_cpp14
    using std::is_null_pointer;
    using std::is_null_pointer_t;
#else
    template <typename type>
    struct is_null_pointer : std::false_type {};
    template <typename type>
    using is_null_pointer_t = get_type<is_null_pointer<type>>;

    template <>
    struct is_null_pointer<std::nullptr_t> : std::true_type {};
#endif

#if bbb_is_cpp17
    using std::void_t;
    using std::bool_constant;
    using std::negation;
    using std::conjunction;
    using std::disjunction;
#else
    /**
     * void_t
     */
    template <typename ...>
    using void_t = void;
    
    /**
     * bool_constant
     */
    template <bool b>
    using bool_constant = std::integral_constant<bool, b>;

    /**
     * negation
     */
    template <typename cond>
    struct negation : bool_constant<!bool(cond::value)> {};

    /**
     * conjunction
     */
    template <typename ... conditions>
    struct conjunction : std::true_type {};

    template <typename cond>
    struct conjunction<cond> : cond {};
    
    template <typename cond, typename ... conditions>
    struct conjunction<cond, conditions ...> : conditional_t<bool(cond::value), conjunction<conditions ...>, cond> {};

    /**
     * disjunction
     */
    template <typename ... conditions>
    struct disjunction : std::false_type {};

    template <typename cond>
    struct disjunction<cond> : cond {};
    
    template <typename cond, typename ... conditions>
    struct disjunction<cond, conditions ...> : conditional_t<bool(cond::value), cond, disjunction<conditions ...>> {};
#endif

    /**
     * is_same
     */
    using std::is_same;

#if bbb_is_cpp14
    template <typename T, typename U>
    constexpr bool is_same_v = is_same<T, U>::value;
#endif

    template <typename T, typename U>
    constexpr bool is_same_f() { return is_same<T, U>::value; };

    /**
     * is_const
     */
    using std::is_const;

#if bbb_is_cpp14
    template <typename T>
    constexpr bool is_const_v = is_const<T>::value;
#endif

    template <typename T>
    constexpr bool is_const_f() {
        return is_const<T>::value;
    }

    /**
     * is_number
     */
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

    /**
     * is_integer
     */
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

    /**
     * is_float
     */
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

    /**
     * remove_const_reference_if_number
     */

    template <typename T>
    using remove_const_reference_if_number = conditional<
        is_number_f<T>(),
        get_type<std::remove_reference<
            get_type<std::remove_const<T>>
        >>,
        T
    >;

    template <typename T>
    using remove_const_reference_if_number_t = get_type<remove_const_reference_if_number<T>>;

    /**
     * add_const_reference_if_not_number
     */

    template <typename T>
    using add_const_reference_if_not_number = conditional<
        !is_number_f<T>(),
        get_type<std::add_const<
            get_type<std::add_lvalue_reference<T>>
        >>,
        T
    >;

    template <typename T>
    using add_const_reference_if_not_number_t = get_type<add_const_reference_if_not_number<T>>;

    /**
     * type_at
     */
    template <std::size_t index, typename ... arguments>
    using type_at = std::tuple_element<index, std::tuple<arguments ...>>;

    template <std::size_t index, typename ... arguments>
    using type_at_t = get_type<type_at<index, arguments ...>>;

    template <std::size_t index, typename ... arguments>
    type_at_t<index, arguments ...> value_at(arguments && ... args) {
        return std::get<index>(std::tuple<arguments ...>(std::forward<arguments>(args) ...));
    };

    template <bool condition, template <typename ...> class t, template <typename ...> class f>
    struct template_conditional {
        template <typename ... arguments>
        using type = get_type<std::conditional<condition, t<arguments ...>, f<arguments ...>>>;
    };

    template <typename cond, typename type = void>
    struct meta_enable_if : enable_if<cond::value, type> {};

    template <typename cond, typename type = void>
    using meta_enable_if_t = enable_if_t<cond::value, type>;

    template <typename cond, typename true_t, typename false_t>
    struct meta_conditional : conditional<cond::value, true_t, false_t> {};
    
    template <typename cond, typename true_t, typename false_t>
    using meta_conditional_t = conditional_t<cond::value, true_t, false_t>;

    template <template <typename ...> class ... meta_conditions>
    struct meta_conjunction {
        template <typename ... args>
        using eval = conjunction<meta_conditions<args ...> ...>;
    };

    template <template <typename ...> class ... meta_conditions>
    struct meta_disjunction {
        template <typename ... args>
        using eval = disjunction<meta_conditions<args ...> ...>;
    };
};
