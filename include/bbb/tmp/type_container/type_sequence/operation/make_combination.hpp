/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_sequence/make_combination.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>
#include <bbb/tmp/type_container/type_sequence/operation/push.hpp>
#include <bbb/tmp/type_container/type_sequence/operation/map.hpp>

namespace bbb {
    namespace tmp {
        namespace type_sequence_operations {
            namespace detail {
                template <typename t, typename meta_sequence>
                struct map_push_front {
                    template <typename sequence>
                    using push_t = push_front_t<t, sequence>;

                    using type = map_t<push_t, meta_sequence>;
                };

                template <typename t, typename meta_sequence>
                using map_push_front_t = get_type<map_push_front<t, meta_sequence>>;
            };

            template <typename ... ts>
            struct make_combination;

            template <typename ... ts>
            using make_combination_t = typename make_combination<ts ...>::type;

            template <typename t, typename ... ts>
            struct make_combination<t, ts ...> {
                using type = concat_t<
                    detail::map_push_front_t<t, make_combination_t<ts ...>>,
                    make_combination_t<ts ...>
                >;
            };

            template <typename t>
            struct make_combination<t> {
                using type = type_sequence<type_sequence<t>, type_sequence<>>;
            };

            template <>
            struct make_combination<> {
                using type = type_sequence<type_sequence<>>;
            };

#if BBB_EXEC_UNIT_TEST
            namespace type_combination_test {
                template <typename ... types>
                using seq = type_sequence<types ...>;
                using test1 = unit_test::assert<
                    make_combination_t<int, char>,
                    type_sequence<seq<int, char>, seq<int>, seq<char>, seq<>>
                >;
                using test2 = unit_test::assert<
                    make_combination_t<int, char, float>,
                    type_sequence<
                        seq<int, char, float>,
                        seq<int, char>,
                        seq<int, float>,
                        seq<int>,
                        seq<char, float>,
                        seq<char>,
                        seq<float>,
                        seq<>
                    >
                >;
            };
#endif
        };
    };
};
