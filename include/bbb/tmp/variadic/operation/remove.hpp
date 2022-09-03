/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/variadic/operation/remove.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>
#include <bbb/tmp/type_container/type_sequence/operation/push.hpp>

namespace bbb {
    namespace tmp {
        namespace variadic_operations {
            template <typename t, typename ... ts>
            struct remove;
            template <typename t, typename ... ts>
            using remove_t = get_type<remove<t, ts ...>>;

            template <typename t, typename u, typename ... ts>
            struct remove<t, u, ts ...> {
                using type = conditional_t<
                is_same_f<t, u>(),
                    type_sequence<ts ...>,
                    type_sequence_operations::push_front_t<u, remove_t<t, ts ...>>
                >;
            };
            template <typename t>
            struct remove<t> { using type = empty_type_sequence; };

#if BBB_EXEC_UNIT_TEST
            namespace remove_test {
                using test1 = unit_test::assert<
                    remove_t<int, int, int, char>,
                    type_sequence<int, char>
                >;
                using test2 = unit_test::assert<
                    remove_t<char, int, int, char>,
                    type_sequence<int, int>
                >;
                using test3 = unit_test::assert<
                    remove_t<char, float, int, char, double>,
                    type_sequence<float, int, double>
                >;
                using test3 = unit_test::assert<
                    remove_t<char, float, int, double>,
                    type_sequence<float, int, double>
                >;
            };
#endif

            template <typename t, typename ... ts>
            struct remove_all;
            template <typename t, typename ... ts>
            using remove_all_t = get_type<remove_all<t, ts ...>>;

            template <typename t, typename u, typename ... ts>
            struct remove_all<t, u, ts ...> {
                using type = conditional_t<
                is_same_f<t, u>(),
                    remove_all_t<t, ts ...>,
                    type_sequence_operations::push_front_t<u, remove_all_t<t, ts ...>>
                >;
            };
            template <typename t>
            struct remove_all<t> { using type = empty_type_sequence; };

#if BBB_EXEC_UNIT_TEST
            namespace remove_all_test {
                using test1 = unit_test::assert<
                    remove_all_t<int, int, int, char>,
                    type_sequence<char>
                >;
                using test2 = unit_test::assert<
                    remove_all_t<char, int, int, char>,
                    type_sequence<int, int>
                >;
                using test3 = unit_test::assert<
                    remove_all_t<char, float, int, char, double>,
                    type_sequence<float, int, double>
                >;
            };
#endif
        };
    };
};
