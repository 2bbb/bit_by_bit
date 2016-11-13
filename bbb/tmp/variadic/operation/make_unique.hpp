/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/variadic/operation/make_unique.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>

#if BBB_EXEC_UNIT_TEST
#   include <bbb/tmp/logic.hpp>
#endif

namespace bbb {
    namespace tmp {
        namespace variadic_operations {
            namespace detail {
                template <typename holder, typename ... types>
                struct make_unique;

                template <typename ... holded_types, typename first, typename ... types>
                struct make_unique<type_sequence<holded_types ...>, first, types ...> {
                    template <typename rhs>
                    using eq = std::is_same<first, rhs>;

                    using type = get_type<conditional_t<
                        any_t<eq, holded_types ...>::value,
                        make_unique<type_sequence<holded_types ...>, types ...>,
                        make_unique<type_sequence<holded_types ..., first>, types ...>
                    >>;
                };

                template <typename ... holded_types>
                struct make_unique<type_sequence<holded_types ...>> {
                    using type = type_sequence<holded_types ...>;
                };
            };

            template <typename ... types>
            using make_unique = detail::make_unique<type_sequence<>, types ...>;
            template <typename ... types>
            using make_unique_t = get_type<make_unique<types ...>>;

#if BBB_EXEC_UNIT_TEST
            namespace variadic_make_unique_test {
                using test1 = unit_test::assert<
                  make_unique_t<int, int>,
                    type_sequence<int>
                >;
                using test2 = unit_test::assert<
                    make_unique_t<int, char, int>,
                    type_sequence<int, char>
                >;
            };
#endif
        };
    };
};