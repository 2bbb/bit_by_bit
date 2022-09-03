/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_set/operation/is_same.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

#include <bbb/tmp/logic.hpp>
#include <bbb/tmp/type_container/type_set/type_set.hpp>
#include <bbb/tmp/type_container/type_set/operation/make_difference.hpp>

namespace bbb {
    namespace tmp {
        namespace type_set_operations {
            template <typename s, typename t>
            using is_same_as_set = make_bool_type_t<
                (make_type_set_t<s>::size == make_type_set_t<t>::size)
                && (make_difference_t<s, t>::size == 0)
            >;

#if BBB_EXEC_UNIT_TEST
            namespace is_same_as_set_test {
                static_assert(tseq_op::make_unique_t<type_sequence<int, int, char>>::size == 2, "test");
                using test1 = unit_test::assert<
                    is_same_as_set<
                        type_sequence<int, int, char>,
                        type_sequence<char, int>
                    >,
                    std::true_type
                >;
                using test2 = unit_test::assert<
                    is_same_as_set<
                        type_sequence<int, int, char, float>,
                        type_sequence<double, char, int>
                    >,
                    std::false_type
                >;
            };
#endif
        };
    };
};
