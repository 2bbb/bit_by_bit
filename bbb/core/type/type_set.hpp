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

#ifndef BBB_TYPE_SET_HPP
#define BBB_TYPE_SET_HPP

#include <bbb/core/type/utility.hpp>
#include <bbb/core/type/range.hpp>
#include <bbb/core/type/logic.hpp>
#include <bbb/core/type/type_holder.hpp>

namespace bbb {
    namespace type_sets {
        template <typename ... types>
        struct type_set {
            using type = make_unique_t<types ...>;
        };

        template <typename ... types>
        using type_set_t = get_type<type_set<types ...>>;

#if BBB_EXEC_UNIT_TEST
        using type_set_test = unit_test::assert<
            type_set_t<int, char, int>,
            type_holder<int, char>
        >;
#endif
    };

    using namespace type_sets;
};

#endif //BBB_TYPE_SET_HPP
