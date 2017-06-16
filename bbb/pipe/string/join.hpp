/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/pipe/string/join.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <string>
#include <sstream>

#include <bbb/core.hpp>

namespace bbb {
    namespace pipe  {
        namespace command {	
            template <
                typename char_type,
                typename traits = std::char_traits<char_type>,
                typename alloc = std::allocator<char_type>
            >
            struct join {
                using string_type = std::basic_string<char_type, traits, alloc>;
                
                join(const string_type &glue) : glue(glue) {}
                join(string_type &&glue) : glue(std::move(glue)) {}
                
                template <typename type>
                friend inline auto operator|(const type &strs, const join &glue)
                -> enable_if_t<
                    is_container<type>::value
                    && !is_kind_of_map<type>::value
                    && is_same<typename type::value_type, string_type>::value,
                    string_type
                > {
                    std::basic_ostringstream<char_type, traits, alloc> joined;
                    for(auto it = std::begin(strs), end = std::end(strs); it != end; ++it) {
                        joined << *it;
                        if(it + 1 != end) joined << glue.glue;
                    }
                    return joined.str();
                }
                
                template <typename type>
                friend inline auto operator|(const type &strs, const join &glue)
                -> enable_if_t<
                    is_container<type>::value
                    && is_kind_of_map<type>::value
                    && is_same<typename type::value_type, string_type>::value,
                    string_type
                > {
                    std::basic_ostringstream<char_type, traits, alloc> joined;
                    for(auto it = std::begin(strs), end = std::end(strs); it != end; ++it) {
                        joined << it->second;
                        if(it + 1 != end) joined << glue.glue;
                    }
                    return joined.str();
                }

            private:
                string_type glue;
            };
        };
        
        template <typename char_type, typename traits, typename alloc>
        static inline auto join(const std::basic_string<char_type, traits, alloc> &str)
        -> command::join<char_type, traits, alloc>
        { return {str}; }
        
        static inline auto join(const char * const str = "")
        -> command::join<char>
        { return {str}; }
    };
};
