/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/builtin_loggers.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/logger/custom_logger.hpp>
#include <bbb/logger/builtin_modules.hpp>

namespace bbb {
	namespace loggers {
		using logger = custom_logger<time_header>;
		using file_logger = custom_logger<file_stream, time_header>;
		using string_logger = custom_logger<string_stream, time_header>;
		using trasher = custom_logger<null_stream>;
		
		namespace {
			logger log;
			file_logger flog;
			string_logger slog;
		}
	};
};
