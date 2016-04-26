/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit test
 * tests/container/delegation.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/misc/simple_test.hpp>

#include <bbb/container/delegation.hpp>

bbb_test_declaretion(container_delegation)

bbb_test_begin_prepare(container_delegation)

    struct int_arrayoid : bbb::container_delegation<std::array<int, 8>> {
        std::array<int, 8> v;
        int_arrayoid() : delegation(v) {}
    };

    struct int_vectroid : bbb::container_delegation<std::vector<int>> {
        std::vector<int> v;
        int_vectroid() : delegation(v) {}
    };

bbb_test_end_prepare(container_delegation)

bbb_test_begin_definition(container_delegation)
        {
            int_arrayoid::value_type t;
            int_arrayoid v;
            bbb_assert(v.size() == 8);
            bbb_assert(!v.empty());
        }

        {
            int_vectroid::value_type t;
            int_vectroid v;
            bbb_assert(v.size() == 0);
            v.push_back(1);
            v.push_back(2);
            bbb_assert(v.size() == 2);
            bbb_assert(v[0] == 1);
            bbb_assert(v[1] == 2);
            v.emplace_back(3);
            bbb_assert(v.size() == 3);
            bbb_assert(v[2] == 3);
        }
bbb_test_end_definition(container_delegation)
