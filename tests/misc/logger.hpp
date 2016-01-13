/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * logger.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include "misc/logger.hpp"
#include "misc/simple_test.hpp"

bbb_test_begin_definition(logger)
        bbb::logger::trace() << "begin logger_test";
        bbb::logger::info("foo") << "foo" << "bar";
        bbb::logger::trace() << "end logger_test";
bbb_test_end_definition(logger)
