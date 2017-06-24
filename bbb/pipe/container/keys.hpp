/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/pipe/container/keys.hpp
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
            struct keys {
                keys(const bool allow_multiple_key)
                : allow_multiple_key(allow_multiple_key) {}

                template <typename map_type>
                friend inline auto operator|(const map_type &hash, keys _)
                    -> type_enable_if_t<
                        disjunction<is_map<map_type>, is_unordered_map<map_type>>,
                        std::vector<typename map_type::key_type>
                    >
                {
                    std::vector<typename map_type::key_type> results;
                    results.reserve(hash.size());
                    for(const auto &pair : hash) results.emplace_back(pair.first);
                    return results;
                }

                template <typename map_type>
                friend inline auto operator|(const map_type &hash, keys _)
                    -> type_enable_if_t<
                        disjunction<is_multimap<map_type>, is_unordered_multimap<map_type>>,
                        std::vector<typename map_type::key_type>
                    >
                {
                    std::vector<typename map_type::key_type> results;
                    results.reserve(hash.size());
                    if(_.allow_multiple_key) {
                        for(const auto &pair : hash) results.emplace_back(pair.first);
                    } else {
                        for(auto it = hash.begin(), end = hash.end(); it != end;) {
                            results.emplace_back(it->first);
                            for(std::size_t i = 0, count = hash.count(it->first); i < count; ++i, ++it);
                        }
                        results.shrink_to_fit();
                    }
                    return results;
                }
            private:
                const bool allow_multiple_key;
            };
        };

        namespace {
            inline command::keys keys(const bool allow_multiple_key = false) { return {allow_multiple_key}; }
            inline command::keys multiple_keys() { return {true}; }
        }
    };
};