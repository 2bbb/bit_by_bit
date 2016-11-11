/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/concat_sequence.hpp
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
        template <typename s, typename t>
        struct concat_sequence;

        template <typename s, typename t>
        using concat_sequence_t = get_type<concat_sequence<s, t>>;

        template <typename ... ss, typename ... ts>
        struct concat_sequence<type_sequence<ss ...>, type_sequence<ts ...>> {
            using type = type_sequence<ss ..., ts ...>;
        };

#if BBB_EXEC_UNIT_TEST
        namespace concat_test {
            using test1 = unit_test::assert<
                concat_sequence_t<type_sequence<int, char>, type_sequence<float, double>>,
                type_sequence<int, char, float, double>
            >;
            using test2 = unit_test::assert<
                concat_sequence_t<type_sequence<int, char>, empty_type_sequence>,
                type_sequence<int, char>
            >;
            using test3 = unit_test::assert<
                concat_sequence_t<empty_type_sequence, type_sequence<float ,double>>,
                type_sequence<float, double>
            >;
            using test4 = unit_test::assert<
                concat_sequence_t<empty_type_sequence, empty_type_sequence>,
                empty_type_sequence
            >;
        };
#endif
    };
};
