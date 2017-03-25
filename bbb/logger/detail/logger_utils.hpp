/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/detail/logger_utils.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/tmp/inheritance.hpp>

#include <bbb/logger/modules.hpp>

namespace bbb {
	namespace loggers {
		namespace detail {
			template <typename ... configs>
			using get_streams_t   = tmp::search_inherited_types_t<stream, console_stream, configs ...>;
			template <typename ... configs>
			using get_header_t    = tmp::search_inherited_type_t<header, header, configs ...>;
			template <typename ... configs>
			using get_footer_t    = tmp::search_inherited_type_t<footer, footer, configs ...>;
			template <typename ... configs>
			using get_separater_t = tmp::search_inherited_type_t<separater, separater, configs ...>;

			template <typename ... configs>
			using logger_basis = tmp::multiple_inheritance<
				detail::get_streams_t<configs ...>,
				detail::get_header_t<configs ...>,
				detail::get_footer_t<configs ...>,
				detail::get_separater_t<configs ...>
			>;

			template <typename holder>
			struct stream_adaptor;

			template <typename type, typename ... types>
			struct stream_adaptor<tmp::type_sequence<type, types ...>> {
				template <typename printer, typename value_type>
				static void print(printer &p, const value_type &v, log_level level) {
					if(level <= p.type::get_log_level()) p.type::os(level) << v;
					stream_adaptor<tmp::type_sequence<types ...>>::print(p, v, level);
				}

				template <typename printer>
				static void print(printer &p, std::ostream& (*f)(std::ostream&), log_level level) {
					if(level <= p.type::get_log_level()) f(p.type::os(level));
					stream_adaptor<tmp::type_sequence<types ...>>::print(p, f, level);
				}

				template <typename printer>
				static void set_log_level(printer &p, log_level level) {
					p.type::set_log_level(level);
					stream_adaptor<tmp::type_sequence<types ...>>::print(p, level);
				}
			};

			template <>
			struct stream_adaptor<tmp::type_sequence<>> {
				template <typename printer, typename value_type>
				static void print(printer &p, const value_type &v, log_level level) {}

				template <typename printer>
				static void print(printer &p, std::ostream& (*f)(std::ostream&), log_level level) {}
				
				template <typename printer>
				static void set_log_level(printer &p, log_level level) {}
			};
		}; // namespace detail
	}; // namepspace loggers
}; // namespace bbb
