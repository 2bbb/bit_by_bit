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

#include <bbb/core.hpp>
#include <bbb/tmp/variadic.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>

namespace bbb {
    namespace tmp {
        namespace type_sequence_operations {
            template <typename t, std::size_t index, typename sequence>
            struct insert;
            template <typename t, std::size_t index, typename sequence>
            using insert_t = get_type<insert<t, index, sequence>>;

            template <typename t, std::size_t index, typename ... ts>
            struct insert<t, index, type_sequence<ts ...>> {
                using type = va_op::insert_t<t, index, ts ...>;
            };

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
};
