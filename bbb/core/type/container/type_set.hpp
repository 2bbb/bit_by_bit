/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/type/type_holder.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/type/utility.hpp>
#include <bbb/core/type/logic.hpp>
#include <bbb/core/type/integer_sequence/integer_range.hpp>

#include <bbb/core/type/container/type_sequence.hpp>
#include <bbb/core/type/container/type_sequence_operation.hpp>

namespace bbb {
    namespace type_sets {
        template <typename ... types>
        struct type_set {
            using type = make_unique_t<types ...>;
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
                type_set_t<char, int, char, char>
            >;
        };
#endif
    };

    using namespace type_sets;
};
