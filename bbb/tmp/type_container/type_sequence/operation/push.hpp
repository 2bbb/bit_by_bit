/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_sequence/operation/push.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>

namespace bbb {
    namespace tmp {
        namespace type_sequence_operations {
            template <typename t, typename sequence>
            struct push_front;

            template <typename t, typename sequence>
            using push_front_t = get_type<push_front<t, sequence>>;

            template <typename t, typename ... types>
            struct push_front<t, type_sequence<types ...>> {
                using type = type_sequence<t, types ...>;
            };

            template <typename t, typename sequence>
            struct push_back;

            template <typename t, typename sequence>
            using push_back_t = get_type<push_back<t, sequence>>;

            template <typename t, typename ... types>
            struct push_back<t, type_sequence<types ...>> {
                using type = type_sequence<types ..., t>;
            };

#if BBB_EXEC_UNIT_TEST
            namespace push_test {
                using test1 = unit_test::assert<
                    push_front_t<int, type_sequence<float, char>>,
                    type_sequence<int, float, char>
                >;
                using test2 = unit_test::assert<
                    push_back_t<char, type_sequence<int, float>>,
                    type_sequence<int, float, char>
                >;
                using test3 = unit_test::assert<
                    push_front_t<int, type_sequence<float, char>>,
                    push_back_t<char, type_sequence<int, float>>
                >;
            };
#endif
        };
    };
};
