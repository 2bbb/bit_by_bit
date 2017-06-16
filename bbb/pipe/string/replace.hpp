/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/pipe.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

namespace bbb {
    namespace pipe  {
        namespace command {
            template <typename char_type, typename traits = std::char_traits<char_type>, typename alloc = std::allocator<char_type>>
            struct replace {
                using string_type = std::basic_string<char_type, traits, alloc>;
                
                replace(const string_type &from, const string_type &to)
                : from(from), to(to) {};
                replace(string_type &&from, string_type &&to)
                : from(std::move(from)), to(std::move(to)) {};
                
                friend inline string_type operator|(const string_type &str, const replace &pair) {
                    string_type result{str};
                    typename string_type::size_type pos;
                    while((pos = result.find(pair.from)) != string_type::npos) {
                        result.replace(pos, pair.from.length(), pair.to);
                    }
                    return result;
                }
                
                friend inline string_type &operator|=(string_type &str, const replace &pair) {
                    typename string_type::size_type pos;
                    while((pos = str.find(pair.from)) != string_type::npos) {
                        str.replace(pos, pair.from.length(), pair.to);
                    }
                    return str;
                }

            private:
                string_type from;
                string_type to;
            };
        };
        
        template <typename char_type, typename traits, typename alloc>
        static inline auto replace(const std::basic_string<char_type, traits, alloc> &from,
                                   const std::basic_string<char_type, traits, alloc> &to)
        -> command::replace<char_type, traits, alloc>
        { return {from, to}; }
        
        static inline auto replace(const char * const from, const char * const to)
        -> command::replace<char>
        { return {from, to}; }
    };
};