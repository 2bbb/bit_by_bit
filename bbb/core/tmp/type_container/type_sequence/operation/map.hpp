/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/tmp/type_container/type_sequence/operation/map.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/tmp/traits.hpp>
#include <bbb/core/tmp/logic.hpp>
#include <bbb/core/tmp/type_container/type_sequence/type_sequence.hpp>

namespace bbb {
    namespace type_sequence_operations {
        template <template <typename> class function, typename ... types>
        struct map_variadic {
            using type = type_sequence<function<types> ...>;
        };

        template <template <typename> class function, typename ... types>
        using map_variadic_t = get_type<map_variadic<function, types ...>>;

        template <template <typename> class function, typename sequence>
        struct map_sequence;

        template <template <typename> class function, typename sequence>
        using map_sequence_t = get_type<map_sequence<function, sequence>>;

        template <template <typename> class function, typename ... types>
        struct map_sequence<function, type_sequence<types ...>> {
            using type = map_variadic_t<function, types ...>;
        };

#if BBB_EXEC_UNIT_TEST
        namespace map_test {
            template <typename type> using and_true = and_type_t<std::true_type, type>;
            using test1 = unit_test::assert<
                map_variadic_t<and_true, std::true_type, std::false_type>,
                type_sequence<std::true_type, std::false_type>
            >;

            template <typename type> using and_false = and_type_t<std::false_type, type>;
            using test2 = unit_test::assert<
                map_variadic_t<and_false, std::true_type, std::false_type>,
                type_sequence<std::false_type, std::false_type>
            >;

            template <typename type> using or_true = or_type_t<std::true_type, type>;
            using test3 = unit_test::assert<
                map_variadic_t<or_true, std::true_type, std::false_type>,
                type_sequence<std::true_type, std::true_type>
            >;
        };
#endif
    };
};
