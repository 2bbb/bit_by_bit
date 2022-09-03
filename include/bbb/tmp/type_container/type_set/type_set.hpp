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

#include <bbb/core.hpp>
#include <bbb/tmp/integer_sequence/operation.hpp>
#include <bbb/tmp/variadic.hpp>
#include <bbb/tmp/type_container/type_sequence.hpp>

namespace bbb {
    namespace tmp {
        namespace type_sets {
            template <typename ... types>
            struct type_set {
                using type = va_op::make_unique_t<types ...>;
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
            using make_type_set = tseq_op::make_unique<sequence>;

            template <typename sequence>
            using make_type_set_t = get_type<make_type_set<sequence>>;
        };

        using namespace type_sets;
    };
};
