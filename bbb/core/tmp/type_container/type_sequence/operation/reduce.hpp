/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/tmp/type_container/type_sequence/operation/reduce.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/tmp/traits.hpp>
#include <bbb/core/tmp/type_container/type_sequence/type_sequence.hpp>
#include <bbb/core/tmp/type_container/type_sequence/operation/push.hpp>

namespace bbb {
    namespace type_sequence_operations {
        template <template <typename, typename> class function, typename initial, typename ... types>
        struct reduce_variadic;

        template <template <typename, typename> class function, typename initial, typename ... types>
        using reduce_variadic_t = get_type<reduce_variadic<function, initial, types ...>>;

        template <template <typename, typename> class function, typename t, typename s, typename ... types>
        struct reduce_variadic<function, t, s, types ...> {
            using type = reduce_variadic_t<function, function<t, s>, types ...>;
        };

        template <template <typename, typename> class function, typename t>
        struct reduce_variadic<function, t> {
            using type = t;
        };

        template <template <typename, typename> class function, typename sequence>
        struct reduce_sequence;

        template <template <typename, typename> class function, typename sequence>
        using reduce_sequence_t = get_type<reduce_sequence<function, sequence>>;

        template <template <typename, typename> class function, typename t, typename ... types>
        struct reduce_sequence<function, type_sequence<t, types ...>> {
            using type = reduce_variadic_t<function, t, types ...>;
        };

#if BBB_EXEC_UNIT_TEST
        namespace reduce_test {
            template <typename seq, typename type>
            using f = push_back_t<type, seq>;
            using test1 = unit_test::assert<
                reduce_variadic_t<f, type_sequence<>, int, char, float>,
                type_sequence<int, char, float>
            >;
            using test2 = unit_test::assert<
                reduce_variadic_t<or_type_t, std::true_type, std::false_type, std::false_type>,
                std::true_type
            >;
            using test3 = unit_test::assert<
                reduce_variadic_t<or_type_t, std::false_type, std::false_type, std::false_type>,
                std::false_type
            >;
            using test4 = unit_test::assert<
                reduce_variadic_t<and_type_t, std::true_type, std::false_type, std::false_type>,
                std::false_type
            >;
            using test5 = unit_test::assert<
                reduce_variadic_t<and_type_t, std::true_type, std::true_type, std::true_type>,
                std::true_type
            >;
        };
#endif
    };
};
