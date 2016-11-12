/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/tmp/type_container/type_sequence/operation/make_direct_product.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/tmp/traits.hpp>
#include <bbb/core/tmp/type_container/type_sequence/type_sequence.hpp>
#include <bbb/core/tmp/type_container/type_sequence/operation/map.hpp>
#include <bbb/core/tmp/type_container/type_sequence/operation/make_unique.hpp>

namespace bbb {
    namespace type_sequence_operations {
        template <typename t, typename u>
        struct make_direct_product;

        template <typename t, typename u>
        using make_direct_product_t = get_type<make_direct_product<t, u>>;

        template <typename ... ts, typename ... us>
        struct make_direct_product<type_sequence<ts ...>, type_sequence<us ...>> {
            template <typename t>
            using make_pair = type_sequence<type_sequence<t, us> ...>;

            using type = reduce_sequence_t<concat_sequence_t, map_variadic_t<make_pair, ts ...>>;
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
            static_assert(make_sequence_unique_t<make_direct_product_t<p, q>>::size == make_sequence_unique_t<p>::size * make_sequence_unique_t<q>::size, "");
        };
#endif
    };
};
