/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/pipe/string/split.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

#include <string>
#include <sstream>

namespace bbb {
    namespace pipe  {
        namespace command {
            template <
                typename char_type,
                typename traits = std::char_traits<char_type>,
                typename alloc = std::allocator<char_type>
            >
            struct split {
                using string_type = std::basic_string<char_type, traits, alloc>;
                
                split(const string_type &delimiter) : delimiter(delimiter) {}
                split(string_type &&delimiter) : delimiter(std::move(delimiter)) {}
                
                friend inline std::vector<string_type> operator|(const std::string &str, const split &delimiter) {
                    std::vector<std::string> splitted;
                    if(delimiter.delimiter.empty()) {
                        for(auto c : str) splitted.emplace_back(1, c);
                        return splitted;
                    }
                    std::size_t pos, last_pos = 0;
                    while((pos = str.find(delimiter.delimiter, last_pos)) != std::string::npos) {
                        splitted.push_back(str.substr(last_pos, pos - last_pos));
                        last_pos = pos + delimiter.delimiter.length();
                    }
                    splitted.push_back(str.substr(last_pos, str.length() - last_pos));
                    return splitted;
                }
                
                friend inline auto operator|(const char_type * const str, const split &delimitter)
                    -> type_enable_if_t<is_character<char_type>, std::vector<string_type>>
                {
                    return string_type(str) | delimitter;
                }

            private:
                string_type delimiter;
            };
        };
        
        namespace {
            template <typename char_type, typename traits, typename alloc>
            inline auto split(const std::basic_string<char_type, traits, alloc> &str)
            -> command::split<char_type, traits, alloc>
            { return {str}; }
            
            inline auto split(const char * const str = "")
            -> command::split<char>
            { return {str}; }
        }
    };
};