/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/custom_logger.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/logger/detail/logger_utils.hpp>
#include <bbb/logger/detail/logger_stream.hpp>
#include <bbb/logger/builtin_modules/streams.hpp>

namespace bbb {
	namespace loggers {
		template <typename ... configs>
		struct custom_logger : detail::logger_basis<configs ...> {
			using stream_types   = detail::get_streams_t<configs ...>;
			using header_type    = detail::get_header_t<configs ...>;
			using footer_type    = detail::get_footer_t<configs ...>;
			using separater_type = detail::get_separater_t<configs ...>;

			using logger_stream = detail::logger_stream<custom_logger>;
			using stream_adaptor = detail::stream_adaptor<stream_types>;

			custom_logger() {}
			
			logger_stream log() {
				return logger_stream(default_tag, default_log_level, *this);;
			}
			logger_stream log(const std::string &tag) {
				return logger_stream(tag, default_log_level, *this);;
			}
			logger_stream log(log_level level) {
				return logger_stream(default_tag, level, *this);;
			}
			logger_stream log(std::string tag, log_level level) {
				return logger_stream(tag, level, *this);;
			}
			template <typename ... arguments>
			inline logger_stream operator()(arguments && ... args) { return log(std::forward<arguments>(args) ...); }
			
			inline logger_stream verbose(std::string tag) { return log(tag, log_level::verbose); }
			inline logger_stream info(std::string tag)    { return log(tag, log_level::info); }
			inline logger_stream warning(std::string tag) { return log(tag, log_level::warning); }
			inline logger_stream error(std::string tag)   { return log(tag, log_level::error); }
			inline logger_stream fatal(std::string tag)   { return log(tag, log_level::fatal); }
			
			inline logger_stream verbose() { return verbose(default_tag); }
			inline logger_stream info()    { return info(default_tag); }
			inline logger_stream warning() { return warning(default_tag); }
			inline logger_stream error()   { return error(default_tag); }
			inline logger_stream fatal()   { return fatal(default_tag); }

			inline void enable() { set_enable(true); }
			inline void disable() { set_enable(false); }
			inline void set_enable(bool enable) { this->enabled = enabled; }
			inline bool is_enabled() const { return enabled; }

			inline void set_default_tag(const std::string &tag) { default_tag = tag; }
			inline void set_default_log_level(log_level level) { default_log_level = level; }

			inline void set_log_level(log_level level) {
				stream_adaptor::set_log_level(*this, level);
			}

			inline void br() { br(default_log_level); }
			inline void br(log_level level) { print(std::endl, level); }
		private:
			log_level default_log_level{log_level::info};
			std::string default_tag{""};
			bool enabled{true};
			
			using header_type::head;
			using footer_type::foot;
			using separater_type::separate;
			
			null_stream ns;
			friend logger_stream;

			template <typename type>
			void print(const type &v, log_level level) {
				if(log_level_manager::is_enabled(level)) {
					stream_adaptor::print(*this, v, level);
				}
			}

			void print(std::ostream& (*f)(std::ostream&), log_level level) {
				if(log_level_manager::is_enabled(level)) {
					stream_adaptor::print(*this, f, level);
				}
			}
		};
	};
};
