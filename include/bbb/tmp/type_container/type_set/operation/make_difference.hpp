/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_set/operation/make_difference.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

#include <bbb/tmp/type_container/type_set/type_set.hpp>

namespace bbb {
    namespace tmp {
        namespace type_set_operations {
            template <typename s, typename t>
            using make_difference = tseq_op::make_difference<make_type_set_t<s>, make_type_set_t<t>>;
            template <typename s, typename t>
            using make_difference_t = get_type<make_difference<s, t>>;

#if BBB_EXEC_UNIT_TEST
            namespace make_difference_test {
                using test1 = unit_test::assert<
                    make_difference_t<
                        type_sequence<int, char, float>,
                        type_sequence<char, float, int>
                    >,
                    empty_type_sequence
                >;
                using test2 = unit_test::assert<
                    make_difference_t<
                        type_sequence<char, float>,
                        type_sequence<char, float, int>
                    >,
                    empty_type_sequence
                >;
                using test3 = unit_test::assert<
                    make_difference_t<
                        type_sequence<int, char, float>,
                        type_sequence<float, int>
                    >,
                    type_sequence<char>
                >;
            };
#endif
        };
    };
};
