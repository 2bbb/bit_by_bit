/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/detail/logger_stream.hpp
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
		namespace detail {
			template <typename logger>
			struct logger_stream {
				logger_stream(std::string tag, log_level level, logger &body)
				: tag(tag)
				, level(level)
				, body(body)
				{
					body.print(body.head(tag, level), level);
				}
				
				~logger_stream() {
					body.print(body.foot(tag, level), level);
					if(without_br) return;
					body.print(std::endl, level);
				}
				
				template <typename type>
				logger_stream &operator<<(const type &v) {
					if(initial) initial = false;
					else body.print(body.separate(), level);
					body.print(v, level);
					return *this;
				}
				logger_stream &operator<<(std::ostream& (*f)(std::ostream&)) {
					body.print(f, level);
					return *this;
				}
				logger_stream &nobr() {
					without_br = true;
					return *this;
				}
			protected:
				std::string tag;
				log_level level;
				logger &body;
				bool without_br{false};
				bool initial{true};
			};
		}; // namespace detail
	}; // namespace loggers
}; // namespace bbb
