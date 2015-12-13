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

#define DeclareTest(name, ...)\
namespace name {\
    void test(##__VA_ARGS__);\
};\

#define BeginDefineTest(name)\
namespace name {

#define EndDefineTest()\
};

#define CarryOutTest(name)\
name::test();