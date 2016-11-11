/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/constants.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#if __cplusplus < 201103L
#   error all you need is C++11 (or later)
#elif __cplusplus < 201402L
#   define bbb_is_cpp11 true
#   define bbb_is_cpp14 false
#else
#   define bbb_is_cpp11 true
#   define bbb_is_cpp14 true
#endif

namespace bbb {
    constexpr bool is_cpp11() { return bbb_is_cpp11; }
    constexpr bool is_cpp14() { return bbb_is_cpp14; }
}

#define BBB_EXEC_UNIT_TEST 1
