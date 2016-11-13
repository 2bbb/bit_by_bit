/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_sequence/operation/make_direct_product.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>
#include <bbb/tmp/type_container/type_sequence/operation/map.hpp>
#include <bbb/tmp/type_container/type_sequence/operation/make_unique.hpp>

namespace bbb {
    namespace tmp {
        namespace type_sequence_operations {
            template <typename t, typename u>
            struct make_direct_product;

            template <typename t, typename u>
            using make_direct_product_t = get_type<make_direct_product<t, u>>;

            template <typename t, typename ... us>
            struct make_direct_product<t, type_sequence<us ...>> {
                template <typename x>
                using make_pair = type_sequence<type_sequence<x, us> ...>;

                using type = reduce_t<concat_t, type_sequence<>, map_t<make_pair, t>>;
            };

#if BBB_EXEC_UNIT_TEST
            namespace make_direct_product_test {
                template <typename ... types>
                using seq = type_sequence<types ...>;
                using test1 = unit_test::assert<
                    make_direct_product_t<seq<int, char>, seq<float, double>>,
                    seq<seq<int, float>, seq<int, double>, seq<char, float>, seq<char, double>>
                >;

                using p = seq<int, int, int, int>;
                using q = seq<char, char, char, char>;
                static_assert(make_direct_product_t<p, q>::size == p::size * q::size, "");
                static_assert(make_unique_t<make_direct_product_t<p, q>>::size == make_unique_t<p>::size * make_unique_t<q>::size, "");
            };
#endif
        };
    };
};
