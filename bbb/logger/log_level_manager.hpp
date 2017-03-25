/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/log_level_managers.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bitset>

#include <bbb/logger/log_level.hpp>

namespace bbb {
	namespace loggers {
		struct log_level_manager {
			static void set_log_level(log_level level) {
				$(log_level::verbose, level <= log_level::verbose);
				$(log_level::info,    level <= log_level::info);
				$(log_level::warning, level <= log_level::warning);
				$(log_level::error,   level <= log_level::error);
				$(log_level::fatal,   level <= log_level::fatal);
			};
			inline static bool is_enabled(log_level level) { return $(level); }
			inline static bool enable(log_level level) { return $(level, true); }
			inline static bool disable(log_level level) { return $(level, false); }
			inline static bool set_enable(log_level level, bool enable) { return $(level, enable); }
		private:
			static std::bitset<static_cast<std::size_t>(log_level::no_logging)> &$() {
				static std::bitset<static_cast<std::size_t>(log_level::no_logging)> _{0xFF};
				return _;
			}
			static constexpr std::size_t to_num(log_level lv) {
				return static_cast<std::size_t>(lv);
			}
			inline static bool $(log_level lv) {
				return $().test(to_num(lv));
			}
			inline static bool $(log_level lv, bool b) {
				return $().set(to_num(lv), b), b;
			}
		};
		
		void set_log_level(log_level lv) {
			log_level_manager::set_log_level(lv);
		};
	};
};