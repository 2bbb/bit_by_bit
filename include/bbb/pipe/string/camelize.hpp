/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/pipe/string/camelize.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/pipe/string/split.hpp>
#include <bbb/pipe/string/join.hpp>
#include <bbb/pipe/string/upper.hpp>
#include <bbb/pipe/functional/map.hpp>

#include <bbb/core.hpp>

#include <string>
#include <algorithm>

namespace bbb {
    namespace pipe  {
        namespace command {	
            struct camelize {
                camelize(const bool upper_camel)
                : upper_camel(upper_camel) {};

                template <
                    typename char_type,
                    typename traits = std::char_traits<char_type>,
                    typename alloc = std::allocator<char_type>
                >
                friend inline auto operator|=(std::basic_string<char_type, traits, alloc> &str, camelize _)
                    -> std::basic_string<char_type, traits, alloc> &
                {
                    str = str
                        | bbb::pipe::split("_")
                        | bbb::pipe::map([](std::string str) { return str |= upper(true); })
                        | bbb::pipe::join("");
                    if(!_.upper_camel) str[0] = ::tolower(str[0]);
                    return str;
                }

                template <
                    typename char_type,
                    typename traits = std::char_traits<char_type>,
                    typename alloc = std::allocator<char_type>
                >
                friend inline auto operator|(std::basic_string<char_type, traits, alloc> str, camelize _)
                    -> std::basic_string<char_type, traits, alloc>
                {
                    return str |= _;
                }

                template <typename char_type>
                friend inline auto operator|(const char_type * const str, camelize _)
                    -> type_enable_if_t<is_character<char_type>, std::basic_string<char_type>>
                {
                    return std::basic_string<char_type>(str) | _;
                }

            private:
                const bool upper_camel;
            };
        };
        namespace {
            inline command::camelize camelize(bool upper_camel = false) { return {upper_camel}; }
            inline command::camelize upper_camelize() { return {true}; }
            inline command::camelize lower_camelize() { return {false}; }
        };
    };
};