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
            template <typename callback_type_>
            struct filter {
                using callback_type = callback_type_;

                filter(callback_type callback)
                : callback(callback) {};
                
                template <typename container_type>
                friend inline auto operator|(const container_type &cont, const filter &cond)
                -> type_enable_if_t<
                    conjunction<
                        is_container<container_type>,
                        negation<is_kind_of_map<container_type>>,
                        negation<is_array<container_type>>
                    >,
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
                -> type_enable_if_t<
                    is_kind_of_map<container_type>,
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
        static inline command::filter<callback_type> filter(callback_type callback)
        { return {callback}; }
    };
};
