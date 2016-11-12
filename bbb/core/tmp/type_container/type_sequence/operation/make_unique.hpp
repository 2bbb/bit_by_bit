/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/tmp/type_container/type_sequence/operation/make_unique.hpp
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
        namespace detail {
            template <typename holder, typename ... types>
            struct make_variadic_unique;

            template <typename ... holded_types, typename first, typename ... types>
            struct make_variadic_unique<type_sequence<holded_types ...>, first, types ...> {
                template <typename rhs>
                using eq = std::is_same<first, rhs>;

                using type = get_type<conditional_t<
                    any_t<eq, holded_types ...>::value,
                    make_variadic_unique<type_sequence<holded_types ...>, types ...>,
                    make_variadic_unique<type_sequence<holded_types ..., first>, types ...>
                >>;
            };
            template <typename ... holded_types>
            struct make_variadic_unique<type_sequence<holded_types ...>> {
                using type = type_sequence<holded_types ...>;
            };
        };

        template <typename ... types>
        using make_variadic_unique = detail::make_variadic_unique<type_sequence<>, types ...>;
        template <typename ... types>
        using make_variadic_unique_t = get_type<make_variadic_unique<types ...>>;

#if BBB_EXEC_UNIT_TEST
        namespace make_unique_test {
            using test1 = unit_test::assert<
                make_variadic_unique_t<int, int>,
                type_sequence<int>
            >;
            using test2 = unit_test::assert<
                make_variadic_unique_t<int, char, int>,
                type_sequence<int, char>
            >;
        }
#endif

        template <typename sequence>
        struct make_sequence_unique;
        template <typename sequence>
        using make_sequence_unique_t = get_type<make_sequence_unique<sequence>>;

        template <typename ... types>
        struct make_sequence_unique<type_sequence<types ...>> {
            using type = make_variadic_unique_t<types ...>;
        };
    };
};
