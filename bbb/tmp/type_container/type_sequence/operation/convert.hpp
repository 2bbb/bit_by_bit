/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/convert.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>
#include <bbb/tmp/integer_sequence/integer_sequence.hpp>

namespace bbb {
    namespace tmp {
        namespace type_sequence_operations {
            template <typename sequence>
            struct from_integer_sequence;
            template <typename sequence>
            using from_integer_sequence_t = get_type<from_integer_sequence<sequence>>;

            template <typename integer_type, integer_type ... ns>
            struct from_integer_sequence<integer_sequence<integer_type, ns ...>> {
                using type = type_sequence<std::integral_constant<integer_type, ns> ...>;
            };

            template <typename sequence>
            struct to_integer_sequence;
            template <typename sequence>
            using to_integer_sequence_t = get_type<to_integer_sequence<sequence>>;

            template <typename integer_type, integer_type ... ns>
            struct to_integer_sequence<type_sequence<std::integral_constant<integer_type, ns> ...>> {
                using type = integer_sequence<integer_type, ns ...>;
            };

#if BBB_EXEC_UNIT_TEST
            namespace convert_test {
                using int_seq = integer_sequence<int, 1, 2, 3, 4>;
                using test1 = unit_test::assert<
                    to_integer_sequence_t<from_integer_sequence_t<int_seq>>,
                    int_seq
                >;

                using typed_int_seq = type_sequence<
                    std::integral_constant<int, 1>,
                    std::integral_constant<int, 3>,
                    std::integral_constant<int, 5>,
                    std::integral_constant<int, 7>
                >;
                using test2 = unit_test::assert<
                    to_integer_sequence_t<typed_int_seq>,
                    integer_sequence<int, 1, 3, 5, 7>
                >;
            };
#endif
        };
    };
};