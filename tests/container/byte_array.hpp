/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * tests/container/byte_array.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/misc/simple_test.hpp>

#include <bbb/container/byte_array.hpp>

bbb_test_begin_definition(byte_array)

    bbb::byte_array<int> barr{0x7FFFFFFF};
    for(auto i = 0; i < barr.size(); i++) {
        std::cout << (int)barr[i] << std::endl;
    }
    for(auto &b : barr) {
        std::cout << (int)b << std::endl;
    }

bbb_test_end_definition(byte_array)
