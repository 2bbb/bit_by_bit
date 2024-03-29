/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/variadic/operation/reduce.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>

#if BBB_EXEC_UNIT_TEST
#   include <bbb/tmp/logic.hpp>
#endif

#include <bbb/core.hpp>

namespace bbb {
    namespace tmp {
        namespace variadic_operations {
            template <template <typename, typename> class function, typename initial, typename ... types>
            struct reduce;

            template <template <typename, typename> class function, typename initial, typename ... types>
            using reduce_t = get_type<reduce<function, initial, types ...>>;

            template <template <typename, typename> class function, typename t, typename s, typename ... types>
            struct reduce<function, t, s, types ...> {
                using type = reduce_t<function, function<t, s>, types ...>;
            };

            template <template <typename, typename> class function, typename t>
            struct reduce<function, t> {
                using type = t;
            };

#if BBB_EXEC_UNIT_TEST
            namespace variadic_reduce_test {
                template <typename seq, typename type>
                using f = type_sequence_operations::push_back_t<type, seq>;
                using test1 = unit_test::assert<
                    reduce_t<f, type_sequence<>, int, char, float>,
                    type_sequence<int, char, float>
                >;
                using test2 = unit_test::assert<
                    reduce_t<or_type_t, std::true_type, std::false_type, std::false_type>,
                    std::true_type
                >;
                using test3 = unit_test::assert<
                    reduce_t<or_type_t, std::false_type, std::false_type, std::false_type>,
                    std::false_type
                >;
                using test4 = unit_test::assert<
                    reduce_t<and_type_t, std::true_type, std::false_type, std::false_type>,
                    std::false_type
                >;
                using test5 = unit_test::assert<
                    reduce_t<and_type_t, std::true_type, std::true_type, std::true_type>,
                    std::true_type
                >;
            };
#endif
        };
    };
};
