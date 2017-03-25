/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/log_level.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <cstdint>
#include <string>

namespace bbb {
	namespace loggers {
		enum struct log_level : std::uint8_t {
			verbose,
			info,
			warning,
			error,
			fatal,
			no_logging
		};

		bool operator<=(log_level lhs, log_level rhs) {
			return static_cast<std::uint8_t>(lhs) <= static_cast<std::uint8_t>(rhs);
		}
		bool operator<(log_level lhs, log_level rhs) {
			return static_cast<std::uint8_t>(lhs) < static_cast<std::uint8_t>(rhs);
		}

		static std::string to_string(log_level level) {
			switch(level) {
				case log_level::verbose: return "verb";
				case log_level::info:    return "info";
				case log_level::warning: return "warn";
				case log_level::error:   return "erro";
				case log_level::fatal:   return "fatl";
				default:      			 return "!!!";
			}
		}
		
		static std::string to_long_string(log_level level) {
			switch(level) {
				case log_level::verbose: return "verbose";
				case log_level::info:    return "info";
				case log_level::warning: return "warning";
				case log_level::error:   return "error";
				case log_level::fatal:   return "fatal";
				default:      			 return "!!!";
			}
		}
	};
};
