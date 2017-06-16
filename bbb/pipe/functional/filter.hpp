/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/pipe/functional/filter.hpp
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
            template <typename argument_type>
            struct filter {
                using callback_type = std::function<bool(argument_type)>;
                filter(callback_type callback)
                : callback(callback) {};
                
                template <typename container_type>
                friend inline auto operator|(const container_type &cont, const filter &cond)
                -> enable_if_t<
                    is_container<container_type>::value
                    && !is_kind_of_map<container_type>::value,
                    container_type
                >
                {
                    container_type results;
                    std::back_insert_iterator<container_type> inserter{results};
                    for(const auto &v : cont) if(cond.callback(v)) *inserter = v;
                    return results;
                }
                
                template <typename container_type>
                friend inline auto operator|(const container_type &cont, const filter &cond)
                -> enable_if_t<
                    is_container<container_type>::value
                    && is_kind_of_map<container_type>::value,
                    container_type
                >
                {
                    container_type results;
                    std::back_insert_iterator<container_type> inserter{results};
                    for(const auto &v : cont) if(cond.callback(v.second)) *inserter = v;
                    return results;
                }
                
            private:
                callback_type callback;
            };
        };
        
        template <typename callback_type>
        static inline auto filter(callback_type callback)
        -> enable_if_t<
            is_callable<callback_type>(callback)
            && is_same<typename function_traits<callback_type>::result_type, bool>::value,
            command::filter<
                typename function_traits<callback_type>::template argument_type<0>
            >
        >
        { return {callback}; }
    };
};
