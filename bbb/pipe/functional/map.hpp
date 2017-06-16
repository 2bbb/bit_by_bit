/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/pipe/functional/map.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <iterator>

#include <bbb/core.hpp>

namespace bbb {
    namespace pipe {
        namespace command {
            template <typename result_type, typename argument_type>
            struct map {
                using callback_type = std::function<result_type(argument_type)>;
                map(callback_type callback)
                : callback(callback) {};
                
                template <typename container>
                friend inline auto operator|(const container &cont, const map &f)
                -> enable_if_t<
                    is_container<container>::value
                    && !is_kind_of_map<container>::value,
                    typename container_traits<container>::template substitute<result_type>
                >
                {
                    using result_container = typename container_traits<container>::template substitute<result_type>;
                    result_container results;
                    std::back_insert_iterator<result_container> inserter{results};
                    for(const auto &v : cont) {
                        *inserter = f.callback(v);
                    }
                    return results;
                }
                
                template <typename container>
                friend inline auto operator|(const container &cont, const map &f)
                -> enable_if_t<
                    is_container<container>::value
                    && is_kind_of_map<container>::value,
                    typename container_traits<container>::template substitute<result_type>
                >
                {
                    using result_container = typename container_traits<container>::template substitute<result_type>;
                    result_container results;
                    std::back_insert_iterator<result_container> inserter{results};
                    for(const auto &v : cont) {
                        *inserter = std::make_pair(v.first, f.callback(v.second));
                    }
                    return results;
                }
                
            private:
                callback_type callback;
            };
        };
        
        template <typename callback_type>
        static inline auto map(callback_type callback)
        -> enable_if_t<
            is_callable<callback_type>(callback),
            command::map<
                typename function_traits<callback_type>::result_type,
                typename function_traits<callback_type>::template argument_type<0>
            >
        >
        { return {callback}; }
    };
};
