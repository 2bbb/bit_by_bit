/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/modules/header.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <string>

#include <bbb/logger/log_level.hpp>

namespace bbb {
	namespace loggers {
		struct header {
			std::string head(std::string tag, log_level level) const {
				return "[ " + to_string(level) + " ] " + ((tag == "") ? "" : (tag + ": "));
			};
		};
	};
};