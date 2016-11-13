/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_sequence/operation/remove.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>

namespace bbb {
    namespace type_sequence_operations {
        template <typename t, typename sequence>
        struct remove;

        template <typename t, typename sequence>
        using remove_t = get_type<remove<t, sequence>>;

        template <typename t, typename u, typename ... types>
        struct remove<t, type_sequence<u, types ...>> {
            using type = conditional_t<
                is_same<t, u>(),
                type_sequence<types ...>,
                push_front_t<u, remove_t<t, type_sequence<types ...>>>
            >;
        };

        template <typename t>
        struct remove<t, type_sequence<>> {
            using type = type_sequence<>;
        };

#if BBB_EXEC_UNIT_TEST
        namespace remove_test {
            using test1 = unit_test::assert<
                remove_t<int, type_sequence<int, int, char>>,
                type_sequence<int, char>
            >;
            using test2 = unit_test::assert<
                remove_t<char, type_sequence<int, int, char>>,
                type_sequence<int, int>
            >;
            using test3 = unit_test::assert<
                remove_t<char, type_sequence<float, int, char, double>>,
                type_sequence<float, int, double>
            >;
            using test3 = unit_test::assert<
                remove_t<char, type_sequence<float, int, double>>,
                type_sequence<float, int, double>
            >;
        };
#endif

        template <typename t, typename sequence>
        struct remove_all;

        template <typename t, typename sequence>
        using remove_all_t = get_type<remove_all<t, sequence>>;

        template <typename t, typename u, typename ... types>
        struct remove_all<t, type_sequence<u, types ...>> {
            using type = conditional_t<
                is_same<t, u>(),
                remove_all_t<t, type_sequence<types ...>>,
                push_front_t<u, remove_all_t<t, type_sequence<types ...>>>
            >;
        };

        template <typename t>
        struct remove_all<t, type_sequence<>> {
            using type = type_sequence<>;
        };

#if BBB_EXEC_UNIT_TEST
        namespace remove_all_test {
            using test1 = unit_test::assert<
                remove_all_t<int, type_sequence<int, int, char>>,
                type_sequence<char>
            >;
            using test2 = unit_test::assert<
                remove_all_t<char, type_sequence<int, int, char>>,
                type_sequence<int, int>
            >;
            using test3 = unit_test::assert<
                remove_all_t<char, type_sequence<float, int, char, double>>,
                type_sequence<float, int, double>
            >;
        };
#endif
    };
};
