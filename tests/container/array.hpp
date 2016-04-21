//
// Created by ISHII 2bit on 2016/04/21.
//

#pragma once

#include <container/array.hpp>
#include <misc/simple_test.hpp>

bbb_test_begin_definition(array)
    {
        bbb::array<int> vec;
        vec.push(1);
        vec.push(2);
        vec.push(3);
        vec.each([](int x){ std::cout << x << std::endl; });
        vec.each([](int x, std::size_t i){ std::cout << i << ":" << x << std::endl; });
        bbb::array<int> other;
        other.push(1);
        other.push(2);
        other.push(3);
        bbb_assert(vec == other);
        other.push(4);
        bbb_assert(vec != other);
    }
bbb_test_end_definition(array)