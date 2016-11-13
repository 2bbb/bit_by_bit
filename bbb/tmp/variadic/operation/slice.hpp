/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/variadic/operation/slice.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/integer_sequence.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>

namespace bbb {
    namespace tmp {
        namespace variadic_operations {
            namespace detail {
                template <typename sequence, typename ... types>
                struct slice;

                template <std::size_t ... indices, typename ... types>
                struct slice<index_sequence<indices ...>, types ...> {
                    using type = type_sequence<type_at_t<indices, types ...> ...>;
                };
            };

            template <std::size_t from, std::size_t length, typename ... types>
            using slice = detail::slice<is_op::make_index_range_t<from, from + length>, types ...>;

            template <std::size_t from, std::size_t length, typename ... types>
            using slice_t = get_type<slice<from, length, types ...>>;

#if BBB_EXEC_UNIT_TEST
            namespace slice_variadic_test {
                using test1 = unit_test::assert<
                    slice_t<0, 2, int, int, char>,
                    type_sequence<int, int>
                >;
                using test2 = unit_test::assert<
                    slice_t<1, 2, int, int, char>,
                    type_sequence<int, char>
                >;
            };
#endif
        };
    };
};
