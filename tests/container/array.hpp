/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit test
 * tests/container/array.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/misc/simple_test.hpp>

#include <bbb/container/array.hpp>

bbb_test_begin_definition(array)
    {
        bbb::array<int> arr;
        arr.push(1);
        arr.push(2);
        arr.push(3);
        arr.each([](int x){ std::cout << x << std::endl; });
        arr.each([](int x, std::size_t i){ std::cout << i << ":" << x << std::endl; });
        {
            bbb::array<int> other;
            other.push(1);
            other.push(2);
            other.push(3);
            bbb_assert(arr == other);
            other.push(4);
            bbb_assert(arr != other);
        }
        {
            auto mapped = arr.map([](int x) -> int { return x * x; });
            bbb::array<int> other;
            other.push(1);
            other.push(4);
            other.push(9);
            bbb_assert(mapped == other);
        }
        bbb_assert(arr.reduce([](int sum, int x) -> int { return sum + x; }) == 1 + 2 + 3);
        bbb_assert(arr.foldr([](int sum, int x) -> int { return sum + x; }) == 1 + 2 + 3);
        bbb_assert(arr.filter([](int x) -> bool { return x % 2 == 0; }) == bbb::array<int>({2}));
        bbb_assert(arr.filter([](int x) -> bool { return x % 2 == 1; }) == bbb::array<int>({1, 3}));
        bbb_assert(
            arr
                .map([](int x) -> int { return x * x; })
                .filter([](int x) -> bool { return x % 2 == 1; })
            == bbb::array<int>({1, 9})
        );
    }
bbb_test_end_definition(array)