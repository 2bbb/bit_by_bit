/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * iterator_utils.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include "container/iterator_utils.hpp"
#include "misc/simple_test.hpp"

#include <iostream>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <map>
#include <string>

bbb_test_begin_prepare(iterator_delegation)
    struct vectroid
        : bbb::iterator_delegation<std::vector<int>> {
        std::vector<int> body;

        vectroid() : delegation(body) { };
    };

    struct mappoid : bbb::iterator_delegation<std::map<int, int>> {
        std::map<int, int> body;

        mappoid() : delegation(body) { };
    };

    struct introid : bbb::iterator_delegation<int> {
        int body;

        introid() : delegation(body) { };
    };
bbb_test_end_prepare(iterator_delegation)

bbb_test_begin_definition(iterator_delegation)

        bbb_assert(bbb::iteratable_class_traits<std::vector<int>>::has_iterator);
        bbb_assert(bbb::iteratable_class_traits<std::vector<int>>::has_reverse_iterator);
        bbb_assert(bbb::iteratable_class_traits<std::map<int, int>>::has_iterator);
        bbb_assert(bbb::iteratable_class_traits<std::string>::has_iterator);
        bbb_assert(!bbb::iteratable_class_traits<int>::has_iterator);
        bbb_assert(bbb::iteratable_class_traits<bbb::iterator_delegation<std::vector<int>>>::has_iterator);

        bbb_assert(bbb::iteratable_class_traits<std::vector<int>>::has_insert);
        bbb_assert(bbb::iteratable_class_traits<std::vector<int>>::has_push_back);
        bbb_assert(!bbb::iteratable_class_traits<std::vector<int>>::has_push_front);

        bbb_assert(bbb::iteratable_class_traits<std::deque<int>>::has_insert);
        bbb_assert(bbb::iteratable_class_traits<std::deque<int>>::has_push_back);
        bbb_assert(bbb::iteratable_class_traits<std::deque<int>>::has_push_front);

        bbb_assert(bbb::iteratable_class_traits<std::list<int>>::has_insert);
        bbb_assert(bbb::iteratable_class_traits<std::list<int>>::has_push_back);
        bbb_assert(bbb::iteratable_class_traits<std::list<int>>::has_push_front);

        bbb_assert(!bbb::iteratable_class_traits<std::queue<int>>::has_insert);
        bbb_assert(!bbb::iteratable_class_traits<std::queue<int>>::has_push_back);
        bbb_assert(!bbb::iteratable_class_traits<std::queue<int>>::has_push_front);

        bbb_assert(!bbb::iteratable_class_traits<int>::has_insert);
        bbb_assert(!bbb::iteratable_class_traits<int>::has_push_back);
        bbb_assert(!bbb::iteratable_class_traits<int>::has_push_front);

        vectroid v;
        v.body.push_back(-1);
        v.body.push_back(-2);
        v.body.push_back(-3);

        std::vector<int> src{1, 2, 3, 4};
        std::copy(src.begin(), src.end(), std::back_inserter(v));
        std::copy(src.begin(), src.end(), std::inserter(v, v.begin()));

        {
            auto it = std::begin(v);
            bbb_assert(*it++ == 1);
            bbb_assert(*it++ == 2);
            bbb_assert(*it++ == 3);
            bbb_assert(*it++ == 4);
            bbb_assert(*it++ == -1);
            bbb_assert(*it++ == -2);
            bbb_assert(*it++ == -3);
            bbb_assert(*it++ == 1);
            bbb_assert(*it++ == 2);
            bbb_assert(*it++ == 3);
            bbb_assert(*it++ == 4);
        }
        mappoid m;
        m.body.insert(std::make_pair(2, 3));
        m.body.insert(std::make_pair(6, 7));
        m.body.insert(std::make_pair(4, 5));
        m.body.insert(std::make_pair(8, 9));
        {
            auto it = std::begin(m);
            bbb_assert(it->first == 2 && (it++)->second == 3);
            bbb_assert(it->first == 4 && (it++)->second == 5);
            bbb_assert(it->first == 6 && (it++)->second == 7);
            bbb_assert(it->first == 8 && (it++)->second == 9);
        }
        introid i;
//	for(auto &it : i) {} // Error: delegated type doesn't provide iterator

bbb_test_end_definition(iterator_delegation)
