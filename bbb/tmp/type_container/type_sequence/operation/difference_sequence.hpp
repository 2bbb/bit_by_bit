/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_sequence/operationdifference_sequence.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/traits.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>

namespace bbb {
    namespace type_sequence_operations {
        /// @struct difference_sequence
        /// calculate difference of sequences
        /// @tparam s: type_sequence
        /// @tparam t: type_sequence
        /// s \ t
        /// ex. {a, b, b, c} \ {a, b, c} == {b}
        ///      {a, b, c} \ {a, b, b, c} == {}
        ///      {c, b, a} \ {a, b, c} == {}
        ///
        template <typename s, typename t>
        struct make_difference;

        /// @struct difference_sequence_t
        /// alias of get_type<diference_sequence<s, t>>
        template <typename s, typename t>
        using make_difference_t = get_type<make_difference<s, t>>;

        template <typename s, typename t, typename ... ts>
        struct make_difference<s, type_sequence<t, ts ...>> {
            using type = make_difference_t<remove_t<t, s>, type_sequence<ts ...>>;
        };

        template <typename s>
        struct make_difference<s, type_sequence<>> {
            using type = s;
        };

#if BBB_EXEC_UNIT_TEST
        namespace difference_sequence_test {
            using test1 = unit_test::assert<
                make_difference_t<type_sequence<int, int, char>, type_sequence<int>>,
                type_sequence<int, char>
            >;
        };
#endif
    };
};
