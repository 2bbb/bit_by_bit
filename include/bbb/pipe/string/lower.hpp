/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/pipe/string/lower.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

#include <string>
#include <algorithm>

namespace bbb {
    namespace pipe  {
        namespace command {	
            struct lower {
                template <
                    typename char_type,
                    typename traits = std::char_traits<char_type>,
                    typename alloc = std::allocator<char_type>
                >
                friend inline auto operator|=(std::basic_string<char_type, traits, alloc> &str, lower)
                    -> std::basic_string<char_type, traits, alloc> &
                {
                    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
                    return str;
                }

                template <
                    typename char_type,
                    typename traits = std::char_traits<char_type>,
                    typename alloc = std::allocator<char_type>
                >
                friend inline auto operator|(std::basic_string<char_type, traits, alloc> str, lower _)
                    -> std::basic_string<char_type, traits, alloc>
                {
                    return str |= _;
                }

                template <typename char_type>
                friend inline auto operator|(const char_type * const str, lower _)
                    -> type_enable_if_t<is_character<char_type>, std::basic_string<char_type>>
                {
                    return std::basic_string<char_type>(str) | _;
                }
            };
        };
        namespace {
            inline command::lower lower() { return {}; }
        }
    };
};