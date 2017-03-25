/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/builtin_modules/footers.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <string>
#include <iomanip>
#include <utility>

#include <bbb/logger/log_level.hpp>
#include <bbb/logger/modules/footer.hpp>
#include <bbb/logger/detail/time_utils.hpp>

namespace bbb {
	namespace loggers {
        struct time_footer : footer {
            std::string foot(std::string tag, log_level level) const {
                return " (at " + time_utils::get_current_date_string() + ")";
            }
            void set_footer_time_format(const std::string &format) {
                this->format = format;
            }
        private:
            std::string format{"%Y/%m/%d %T"};
        };

        struct elapsed_time_footer : footer {
            std::string foot(std::string tag, log_level level) const {
                return " (elapsed " + std::to_string(time_utils::get_elapsed_time()) + ")";
            }
        };
    };
};