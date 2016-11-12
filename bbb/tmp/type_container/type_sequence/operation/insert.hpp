/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_sequence/operation/insert.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/traits.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>
#include <bbb/tmp/type_container/type_sequence/operation/push.hpp>

namespace bbb {
    namespace type_sequence_operations {
        namespace detail {
            template <typename x, std::size_t index, typename sequence, std::size_t current_index, bool = current_index < index>
            struct insert;
            template <typename x, std::size_t index, typename sequence, std::size_t current_index>
            using insert_t = get_type<insert<x, index, sequence, current_index>>;

            template <typename x, std::size_t index, typename t, typename ... types, std::size_t current_index>
            struct insert<x, index, type_sequence<t, types ...>, current_index, true> {
                using type = push_front_t<t, insert_t<x, index, type_sequence<types ...>, current_index + 1>>;
            };
            template <typename x, std::size_t index, typename ... types, std::size_t current_index>
            struct insert<x, index, type_sequence<types ...>, current_index, false> {
                using type = type_sequence<x, types ...>;
            };
        };

        template <typename t, std::size_t index, typename sequence>
        using insert = detail::insert<t, index, sequence, 0>;

        template <typename t, std::size_t index, typename sequence>
        using insert_t = get_type<insert<t, index, sequence>>;

#if BBB_EXEC_UNIT_TEST
        namespace insert_test {
            using test0 = unit_test::assert<
                insert_t<int, 0, type_sequence<char, float>>,
                type_sequence<int, char, float>
            >;
            using test1 = unit_test::assert<
                insert_t<int, 1, type_sequence<char, float>>,
                type_sequence<char, int, float>
            >;
            using test2 = unit_test::assert<
                insert_t<int, 2, type_sequence<char, float>>,
                type_sequence<char, float, int>
            >;
        };
#endif
    };
};
