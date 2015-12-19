/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * simple_test.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once
#include <cassert>
#include <iostream>

#define bbb_test_declaretion(name)\
namespace name##_test { void test(); };

#define bbb_test_begin_definition(name)\
namespace name##_test {\
    std::size_t total{0};\
    std::size_t success{0};\
    std::size_t failure{0};\
    void test() {

#define bbb_test_end_definition()\
   }\
};

#define bbb_test_begin_prepare(name)\
namespace name##_test {

#define bbb_test_end_prepare(name) };

#define bbb_test(name) name##_test::test();

#define bbb_assert(...) {\
    total++;\
    if(__VA_ARGS__) {\
        success++;\
        std::cout << "passed     [" << success << "/" << total << "] " << #__VA_ARGS__ << std::endl;\
    } else {\
        failure++;\
        std::cout << "failure... [" << failure << "/" << total << "] " #__VA_ARGS__ << std::endl;\
    }\
}