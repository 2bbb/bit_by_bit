/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/builtin_modules/separaters.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/logger/modules/separater.hpp>

namespace bbb {
	namespace loggers {
		struct camma_separater : separater {
			std::string separate() const { return ", "; };
		};

		struct space_separater : separater {
			std::string separate() const { return " "; };
		};
	};
};
