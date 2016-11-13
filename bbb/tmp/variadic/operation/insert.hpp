/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/variadic/operation/insert.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>
#include <bbb/tmp/type_container/type_sequence/operation/push.hpp>

namespace bbb {
    namespace tmp {
        namespace variadic_operations {
            namespace detail {
                template <
                    typename x,
                    std::size_t index,
                    std::size_t current_index,
                    bool is_current_index_eq_index,
                    typename ... ts
                >
                struct insert;

                template <typename x, std::size_t index, std::size_t current_index, typename ... ts>
                struct insert<x, index, current_index, true, ts ...> {
                    using type = type_sequence<x, ts ...>;
                };

                template <typename x,  std::size_t index,  std::size_t current_index, typename t, typename ... ts>
                struct insert<x, index, current_index, false, t, ts ...> {
                    using type = type_sequence_operations::push_front_t<
                        t,
                        get_type<insert<x, index, current_index + 1, index == (current_index + 1), ts ...>>
                    >;
                };
            };

            template <typename t, std::size_t index, typename ... ts>
            struct insert {
                static_assert(index <= sizeof...(ts), "[variadic insert] out of bounds");
                using type = conditional_t<
                    index == 0,
                    type_sequence<t, ts ...>,
                    conditional_t<
                        index == sizeof...(ts),
                        type_sequence<ts ..., t>,
                        get_type<detail::insert<t, index, 0, index == 0, ts ...>>
                    >
                >;
            };

            template <typename t, std::size_t index, typename ... ts>
            using insert_t = get_type<insert<t, index, ts ...>>;

#if BBB_EXEC_UNIT_TEST
            namespace insert_test {
                using test0 = unit_test::assert<
                    insert_t<int, 0, char, float>,
                    type_sequence<int, char, float>
                >;
                using test1 = unit_test::assert<
                    insert_t<int, 1, char, float>,
                    type_sequence<char, int, float>
                >;
                using test2 = unit_test::assert<
                    insert_t<int, 2, char, float>,
                    type_sequence<char, float, int>
                >;
            };
#endif
        };
    };
};
