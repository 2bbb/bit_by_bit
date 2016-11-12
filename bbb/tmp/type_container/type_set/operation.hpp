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

#include <bbb/core/traits.hpp>
#include <bbb/tmp/integer_sequence/integer_range.hpp>

#include <bbb/tmp/type_container/type_set/type_set.hpp>

namespace bbb {
    namespace type_set_operations {
        template <typename s, typename t>
        using is_same_as_set = conditional_t<
            (make_sequence_unique_t<s>::size == make_sequence_unique_t<t>::size)
            && (difference_sequence_t<make_sequence_unique_t<s>, make_sequence_unique_t<t>>::size == 0),
            std::true_type,
            std::false_type
        >;

#if BBB_EXEC_UNIT_TEST
        namespace is_same_as_set_test {
            static_assert(make_sequence_unique_t<type_sequence<int, int, char>>::size == 2, "test");
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
        using difference_set = difference_sequence<make_type_set_t<s>, make_type_set_t<t>>;
        template <typename s, typename t>
        using difference_set_t = get_type<difference_set<s, t>>;
    };

    using namespace type_set_operations;
};
