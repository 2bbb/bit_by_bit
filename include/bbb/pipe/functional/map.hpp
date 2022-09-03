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

#include <bbb/core.hpp>

#include <iterator>

namespace bbb {
    namespace pipe {
        namespace command {
            template <typename callback_type_>
            struct map {
                using callback_type = callback_type_;
                template <typename container, typename map>
                using result_container_type = typename container_traits<container>::template substitute<
                    get_type<detect_result_type<typename map::callback_type, typename container::value_type>>
                >;

                map(callback_type callback)
                : callback(callback) {};
                
                template <typename container>
                friend inline auto operator|(const container &cont, const map &f)
                -> type_enable_if_t<
                    conjunction<
                        is_container<container>,
                        negation<is_kind_of_map<container>>,
                        negation<is_array<container>>
                    >,
                    result_container_type<container, map>
                >
                {
                    using result_container = result_container_type<container, map>;
                    result_container results;
                    std::back_insert_iterator<result_container> inserter{results};
                    for(const auto &v : cont) {
                        *inserter = f.callback(v);
                    }
                    return results;
                }
                
                template <typename container>
                friend inline auto operator|(const container &cont, const map &f)
                -> type_enable_if_t<
                    is_array<container>,
                    result_container_type<container, map>
                >
                {
                    using result_container = result_container_type<container, map>;
                    result_container results;
                    for(std::size_t i = 0; i < cont.size(); ++i) {
                        results[i] = f.callback(cont[i]);
                    }
                    return results;
                }
                
                template <typename container>
                friend inline auto operator|(const container &cont, const map &f)
                -> type_enable_if_t<
                    is_kind_of_map<container>,
                    result_container_type<container, map>
                >
                {
                    using result_container = result_container_type<container, map>;
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
        
        namespace {
            template <typename callback_type>
            inline command::map<callback_type> map(callback_type callback)
            { return {callback}; }
        }
    };
};
