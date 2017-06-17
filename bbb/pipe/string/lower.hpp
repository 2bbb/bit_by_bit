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

#include <string>
#include <algorithm>

#include <bbb/core.hpp>

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
            };
        };
        command::lower lower() { return {}; }
    };
};