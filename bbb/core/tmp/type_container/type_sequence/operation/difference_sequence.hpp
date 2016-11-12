/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/tmp/type_container/type_sequence/operationdifference_sequence.hpp
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
        struct difference_sequence;

        /// @struct difference_sequence_t
        /// alias of get_type<diference_sequence<s, t>>
        template <typename s, typename t>
        using difference_sequence_t = get_type<difference_sequence<s, t>>;

        template <typename s, typename t, typename ... ts>
        struct difference_sequence<s, type_sequence<t, ts ...>> {
            using type = difference_sequence_t<remove_t<t, s>, type_sequence<ts ...>>;
        };

        template <typename s>
        struct difference_sequence<s, type_sequence<>> {
            using type = s;
        };

#if BBB_EXEC_UNIT_TEST
        namespace difference_sequence_test {
            using test1 = unit_test::assert<
                difference_sequence_t<type_sequence<int, int, char>, type_sequence<int>>,
                type_sequence<int, char>
            >;
        };
#endif
    };
};
