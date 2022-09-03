/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/pipe/container/values.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

namespace bbb {
    namespace pipe {
        namespace command {
            struct values {
                template <typename map_type>
                friend inline auto operator|(const map_type &hash, values)
                    -> type_enable_if_t<
                        is_kind_of_map<map_type>,
                        std::vector<typename map_type::mapped_type>
                    >
                {
                    std::vector<typename map_type::mapped_type> results;
                    results.reserve(hash.size());
                    for(const auto &pair : hash) results.emplace_back(pair.second);
                    return results;
                }
            };
        };
        namespace {
            inline command::values values() { return {}; }
        }
    };
};