/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_set/type_set.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/traits.hpp>
#include <bbb/tmp/integer_sequence/integer_range.hpp>
#include <bbb/tmp/type_container/type_sequence.hpp>

namespace bbb {
    namespace type_sets {
        template <typename ... types>
        struct type_set {
            using type = make_variadic_unique_t<types ...>;
        };

        template <typename ... types>
        using type_set_t = get_type<type_set<types ...>>;

#if BBB_EXEC_UNIT_TEST
        namespace type_set_test {
            using test1 = unit_test::assert<
                type_set_t<int, char, int>,
                type_sequence<int, char>
            >;
            using test2 = unit_test::assert<
                type_set_t<int, char, int>,
                type_set_t<int, char, char>
            >;
        };
#endif

        template <typename sequence>
        struct make_type_set;

        template <typename sequence>
        using make_type_set_t = get_type<make_type_set<sequence>>;

        template <typename ... types>
        struct make_type_set<type_sequence<types ...>> {
            using type = type_set_t<types ...>;
        };
    };

    using namespace type_sets;
};
