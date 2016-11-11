/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/type/container/type_combination.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/tmp/type_container/type_sequence.hpp>
#include <bbb/core/tmp/type_container/type_set.hpp>

namespace bbb {
    namespace type_combinations {
        namespace detail {
            template <typename t, typename meta_sequence>
            struct map_push_front {
                template <typename sequence>
                using push_t = push_front_t<t, sequence>;

                using type = map_sequence_t<push_t, meta_sequence>;
            };

            template <typename t, typename meta_sequence>
            using map_push_front_t = get_type<map_push_front<t, meta_sequence>>;
        };

        template <typename ... ts>
        struct type_combination;

        template <typename ... ts>
        using type_combination_t = typename type_combination<ts ...>::type;

        template <typename t, typename ... ts>
        struct type_combination<t, ts ...> {
            using type = concat_sequence_t<
                detail::map_push_front_t<t, type_combination_t<ts ...>>,
                type_combination_t<ts ...>
            >;
        };

        template <typename t>
        struct type_combination<t> {
            using type = type_sequence<type_sequence<t>, type_sequence<>>;
        };

        template <>
        struct type_combination<> {
            using type = type_sequence<type_sequence<>>;
        };

#if BBB_EXEC_UNIT_TEST
        namespace type_combination_test {
            template <typename ... types>
            using seq = type_sequence<types ...>;
            using test1 = unit_test::assert<
                type_combination_t<int, char>,
                type_sequence<seq<int, char>, seq<int>, seq<char>, seq<>>
            >;
            using test2 = unit_test::assert<
                type_combination_t<int, char, float>,
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
    using namespace type_combinations;
};
