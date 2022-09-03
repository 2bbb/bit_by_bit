/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/modules/stream.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <iostream>

#include <bbb/logger/log_level.hpp>

namespace bbb {
	namespace loggers {
		struct stream {
			std::ostream &os(log_level level) {
				return std::cout;
			}
			void set_log_level(log_level level) {
				this->level = level;
			}
			log_level get_log_level() const {
				return level;
			}
		private:
			log_level level;
		};

		struct console_stream : stream {
			std::ostream &os(log_level level) {
				if(level <= log_level::warning)	return std::cout;
				else							return std::cerr;
			}
		};
	};
};
