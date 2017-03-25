/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/builtin_modules/streams.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <bbb/logger/log_level.hpp>
#include <bbb/logger/modules/stream.hpp>

namespace bbb {
	namespace loggers {
		struct error_stream : stream {
			std::ostream &os(log_level level) { return std::cerr; }
		};
		
		struct file_stream : stream {
			virtual ~file_stream() { if(ofs.is_open()) ofs.close(); }
			bool open(const std::string &path, std::ostream::open_mode mode = std::ios::out | std::ios::app) {
				if(ofs.is_open()) ofs.close();
				
				ofs.open(path, mode);
				if(ofs.fail()) {
					file_path = path;
					ofs.close();
					return false;
				} else {
					file_path = "";
					return true;
				}
			}
			bool is_open() const { return ofs.is_open(); }
			std::streamsize file_size() const {
				if(file_path == "") return -1;
				std::ifstream ifs(file_path, std::ios::in);
				return ifs.seekg(0, std::ios::end).tellg();
			}

			std::string opened_path() const { return file_path; }
			std::ostream &os(log_level level) { return ofs; }
		private:
			std::ofstream ofs;
			std::string file_path;
		};
		
		struct string_stream : stream {
			std::ostream &os(log_level level) { return ss; }
			std::string text() { return ss.str(); }
			void clear() { ss.clear(); }
		private:
			std::stringstream ss;
		};
		
		struct null_streambuf : public std::streambuf {
		private:
			virtual int overflow(char c) {
				return traits_type::not_eof(c);
			}
		};
		
		struct null_ostream : public std::ostream {
			null_streambuf streambuf;
		public:
			null_ostream() : std::ostream(&streambuf){}
		};
		static null_ostream nout;

		struct null_stream : stream {
			std::ostream &os(log_level level) { return nout; }
		};
	};
};
