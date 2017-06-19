/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/pipe/string/upper.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <string>
#include <algorithm>

#include <bbb/core.hpp>

namespace bbb {
    namespace pipe  {
        namespace command {	
            struct upper {
                upper(const bool head_only)
                : head_only(head_only) {};

                template <
                    typename char_type,
                    typename traits = std::char_traits<char_type>,
                    typename alloc = std::allocator<char_type>
                >
                friend inline auto operator|=(std::basic_string<char_type, traits, alloc> &str, upper _)
                    -> std::basic_string<char_type, traits, alloc> &
                {
                    if(str.empty()) return str;

                    if(_.head_only) str[0] = ::toupper(str[0]);
                    else std::transform(str.begin(), str.end(), str.begin(), ::toupper);

                    return str;
                }

                template <
                    typename char_type,
                    typename traits = std::char_traits<char_type>,
                    typename alloc = std::allocator<char_type>
                >
                friend inline auto operator|(std::basic_string<char_type, traits, alloc> str, upper _)
                    -> std::basic_string<char_type, traits, alloc>
                {
                    return str |= _;
                }

                template <typename char_type>
                friend inline auto operator|(const char_type * const str, upper _)
                    -> std::basic_string<char_type>
                {
                    return std::basic_string<char_type>(str) | _;
                }
            private:
                const bool head_only;
            };
        };
        command::upper upper(bool head_only = false) { return {head_only}; }
    };
};