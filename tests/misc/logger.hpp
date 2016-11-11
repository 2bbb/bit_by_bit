/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * tests/misc/logger.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/misc/simple_test.hpp>

#include <bbb/misc/logger.hpp>

bbb_test_begin_definition(logger)
        bbb::logger::trace() << "begin logger_test";
        bbb::logger::info("foo") << "foo" << "bar";
        bbb::logger::trace() << "end logger_test";
        bbb::logger::manager::add_logger("test", &std::cout, bbb::logger::style::separater::csv, bbb::logger::style::header::timestamp);
        bbb::logger::info("test") << "timestmap";
        bbb::logger::info("test") << "timestmap";
bbb_test_end_definition(logger)
