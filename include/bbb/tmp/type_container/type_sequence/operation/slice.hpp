/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_sequence/operation/slice.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/variadic.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>

namespace bbb {
    namespace tmp {
        namespace type_sequence_operations {
            template <std::size_t from, std::size_t to, typename sequence>
            struct slice;
            template <std::size_t from, std::size_t to, typename sequence>
            using slice_t = get_type<slice<from, to, sequence>>;

            template <std::size_t from, std::size_t to, typename ... types>
            struct slice<from, to, type_sequence<types ...>> {
                using type = va_op::slice_t<from, to, types ...>;
            };

#if BBB_EXEC_UNIT_TEST
            namespace slice_type_sequence_test {
                using test1 = unit_test::assert<
                    slice_t<0, 2, type_sequence<int, int, char>>,
                    type_sequence<int, int>
                >;
                using test2 = unit_test::assert<
                    slice_t<1, 2, type_sequence<int, int, char>>,
                    type_sequence<int, char>
                >;
            };
#endif
        };
    };
};
