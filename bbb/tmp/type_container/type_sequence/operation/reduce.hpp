/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_sequence/operation/reduce.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/variadic.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>
#include <bbb/tmp/type_container/type_sequence/operation/push.hpp>

namespace bbb {
    namespace tmp {
        namespace type_sequence_operations {
            template <template <typename, typename> class function, typename initial, typename sequence>
            struct reduce;

            template <template <typename, typename> class function, typename initial, typename sequence>
            using reduce_t = get_type<reduce<function, initial, sequence>>;

            template <template <typename, typename> class function, typename initial, typename ... types>
            struct reduce<function, initial, type_sequence<types ...>> {
                using type = va_op::reduce_t<function, initial, types ...>;
            };

#if BBB_EXEC_UNIT_TEST
            namespace sequence_reduce_test {
                template <typename ... ts>
                using seq = type_sequence<ts ...>;

                template <typename seq, typename type>
                using f = push_back_t<type, seq>;
                using test1 = unit_test::assert<
                    reduce_t<f, type_sequence<>, seq<int, char, float>>,
                    type_sequence<int, char, float>
                >;
                using test2 = unit_test::assert<
                    reduce_t<or_type_t, std::true_type, seq<std::false_type, std::false_type>>,
                    std::true_type
                >;
                using test3 = unit_test::assert<
                    reduce_t<or_type_t, std::false_type, seq<std::false_type, std::false_type>>,
                    std::false_type
                >;
                using test4 = unit_test::assert<
                    reduce_t<and_type_t, std::true_type, seq<std::false_type, std::false_type>>,
                    std::false_type
                >;
                using test5 = unit_test::assert<
                    reduce_t<and_type_t, std::true_type, seq<std::true_type, std::true_type>>,
                    std::true_type
                >;
            };
#endif
        };
    };
};
