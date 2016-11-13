/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_set/operation.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

#include <bbb/tmp/integer_sequence/operation.hpp>
#include <bbb/tmp/type_container/type_set/type_set.hpp>

namespace bbb {
    namespace type_set_operations {
        template <typename s, typename t>
        using is_same_as_set = conditional_t<
            (tseq_op::make_unique_t<s>::size == tseq_op::make_unique_t<t>::size)
            && (tseq_op::make_difference_t<tseq_op::make_unique_t<s>, tseq_op::make_unique_t<t>>::size == 0),
            std::true_type,
            std::false_type
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

        template <typename s, typename t>
        using make_difference = tseq_op::make_difference<make_type_set_t<s>, make_type_set_t<t>>;
        template <typename s, typename t>
        using make_difference_t = get_type<make_difference<s, t>>;
    };

    namespace tset_op = type_set_operations;
};
