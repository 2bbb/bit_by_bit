/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/slice.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/tmp/traits.hpp>
#include <bbb/core/tmp/type_container/type_sequence/type_sequence.hpp>

namespace bbb {
    namespace type_sequence_operations {
        namespace detail {
            template <typename sequence, typename ... types>
            struct slice;

            template <std::size_t ... indices, typename ... types>
            struct slice<index_sequence<indices ...>, types ...> {
                using type = type_sequence<type_at<indices, types ...> ...>;
            };
        };

        template <std::size_t from, std::size_t to, typename ... types>
        using slice = detail::slice<index_range<from, to>, types ...>;

        template <std::size_t from, std::size_t to, typename ... types>
        using slice_t = get_type<slice<from, to, types ...>>;

#if BBB_EXEC_UNIT_TEST
        namespace slice_test {
            using test1 = unit_test::assert<
                slice_t<0, 1, int, int, char>,
                type_sequence<int, int>
            >;
            using test2 = unit_test::assert<
                slice_t<1, 2, int, int, char>,
                type_sequence<int, char>
            >;
        }
#endif

        template <std::size_t from, std::size_t to, typename sequence>
        struct slice_type_sequence;

        template <std::size_t from, std::size_t to, typename ... types>
        struct slice_type_sequence<from, to, type_sequence<types ...>> {
            using type = slice_t<from, to, types ...>;
        };

        template <std::size_t from, std::size_t to, typename sequence>
        using slice_type_sequence_t = get_type<slice_type_sequence<from, to, sequence>>;

#if BBB_EXEC_UNIT_TEST
        namespace slice_type_sequence_test {
            using test1 = unit_test::assert<
                slice_type_sequence_t<0, 1, type_sequence<int, int, char>>,
                type_sequence<int, int>
            >;
            using test2 = unit_test::assert<
                slice_type_sequence_t<1, 2, type_sequence<int, int, char>>,
                type_sequence<int, char>
            >;
        };
#endif
    };
};
