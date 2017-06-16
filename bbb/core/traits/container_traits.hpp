/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/traits/container_traits.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bitset>
#include <array>

#include <vector>
#include <deque>
#include <forward_list>
#include <list>

#include <map>
#include <unordered_map>

#include <set>
#include <unordered_set>

#include <initializer_list>

#include <bbb/core/basic.hpp>
#include <bbb/core/traits/type_traits.hpp>

namespace bbb {
    namespace container_info {
        template <bool b>
        using bool_type = conditional<b, std::true_type, std::false_type>;
        template <bool b>
        using bool_type_t = conditional_t<b, std::true_type, std::false_type>;
        
        enum class container_type_tag {
            bitset,
            array,
            vector,
            deque,
            forward_list,
            list,
            map,
            multimap,
            unordered_map,
            unordered_multimap,
            set,
            multiset,
            unordered_set,
            unordered_multiset,
            unknown,
            not_container,
        };
        
        template <typename container, typename type>
        struct substitute;

        template <typename container, typename type>
        using substitute_t = get_type<substitute<container, type>>;

        template <typename type>
        struct is_bitset : std::false_type {};
        template <std::size_t size>
        struct is_bitset<std::bitset<size>> : std::true_type {};
        
        template <typename type>
        struct is_array : std::false_type {};
        template <typename type, std::size_t size>
        struct is_array<std::array<type, size>> : std::true_type {};
        
        template <typename value_type, std::size_t size, typename new_type>
        struct substitute<std::array<value_type, size>, new_type> {
            using type = std::array<new_type, size>;
        };
        
        template <typename type>
        struct is_vector : std::false_type {};
        template <typename type, typename alloc>
        struct is_vector<std::vector<type, alloc>> : std::true_type {};
        
        template <typename value_type, typename alloc, typename new_type>
        struct substitute<std::vector<value_type, alloc>, new_type> {
            using type = std::vector<new_type>;
        };
        
        template <typename type>
        struct is_deque : std::false_type {};
        template <typename type, typename alloc>
        struct is_deque<std::deque<type, alloc>> : std::true_type {};
        
        template <typename value_type, typename alloc, typename new_type>
        struct substitute<std::deque<value_type, alloc>, new_type> {
            using type = std::deque<new_type>;
        };

        template <typename type>
        struct is_forward_list : std::false_type {};
        template <typename type, typename alloc>
        struct is_forward_list<std::forward_list<type, alloc>> : std::true_type {};
        
        template <typename value_type, typename alloc, typename new_type>
        struct substitute<std::forward_list<value_type, alloc>, new_type> {
            using type = std::forward_list<new_type>;
        };

        template <typename type>
        struct is_list : std::false_type {};
        template <typename type, typename alloc>
        struct is_list<std::list<type, alloc>> : std::true_type {};
        
        template <typename value_type, typename alloc, typename new_type>
        struct substitute<std::list<value_type, alloc>, new_type> {
            using type = std::list<new_type>;
        };

        template <typename type>
        struct is_map : std::false_type {};
        template <typename key, typename value, typename compare, typename alloc>
        struct is_map<std::map<key, value, compare, alloc>> : std::true_type {};
        
        template <typename key, typename value, typename compare, typename alloc, typename new_type>
        struct substitute<std::map<key, value, compare, alloc>, new_type> {
            using type = std::map<key, new_type>;
        };

        template <typename type>
        struct is_multimap : std::false_type {};
        template <typename key, typename value, typename compare, typename alloc>
        struct is_multimap<std::multimap<key, value, compare, alloc>> : std::true_type {};
        
        template <typename key, typename value, typename compare, typename alloc, typename new_type>
        struct substitute<std::multimap<key, value, compare, alloc>, new_type> {
            using type = std::multimap<key, new_type>;
        };

        template <typename type>
        struct is_unordered_map : std::false_type {};
        template <typename key, typename value, typename hash, typename pred, typename alloc>
        struct is_unordered_map<std::unordered_map<key, value, hash, pred, alloc>> : std::true_type {};
        
        template <typename key, typename value, typename hash, typename pred, typename alloc, typename new_type>
        struct substitute<std::unordered_map<key, value, hash, pred, alloc>, new_type> {
            using type = std::unordered_map<key, new_type>;
        };
        
        template <typename type>
        struct is_unordered_multimap : std::false_type {};
        template <typename key, typename value, typename hash, typename pred, typename alloc>
        struct is_unordered_multimap<std::unordered_multimap<key, value, hash, pred, alloc>> : std::true_type {};
        
        template <typename key, typename value, typename hash, typename pred, typename alloc, typename new_type>
        struct substitute<std::unordered_multimap<key, value, hash, pred, alloc>, new_type> {
            using type = std::unordered_multimap<key, new_type>;
        };
        
        template <typename type>
        struct is_set : std::false_type {};
        template <typename key, typename compare, typename alloc>
        struct is_set<std::set<key, compare, alloc>> : std::true_type {};
        
        template <typename key, typename compare, typename alloc, typename new_type>
        struct substitute<std::set<key, compare, alloc>, new_type> {
            using type = std::set<new_type>;
        };

        template <typename type>
        struct is_multiset : std::false_type {};
        template <typename key, typename compare, typename alloc>
        struct is_multiset<std::multiset<key, compare, alloc>> : std::true_type {};
        
        template <typename key, typename compare, typename alloc, typename new_type>
        struct substitute<std::multiset<key, compare, alloc>, new_type> {
            using type = std::multiset<new_type>;
        };

        template <typename type>
        struct is_unordered_set : std::false_type {};
        template <typename key, typename hash, typename pred, typename alloc>
        struct is_unordered_set<std::unordered_set<key, hash, pred, alloc>> : std::true_type {};
        
        template <typename key, typename hash, typename pred, typename alloc, typename new_type>
        struct substitute<std::unordered_set<key, hash, pred, alloc>, new_type> {
            using type = std::unordered_set<new_type>;
        };
        
        template <typename type>
        struct is_unordered_multiset : std::false_type {};
        template <typename key, typename hash, typename pred, typename alloc>
        struct is_unordered_multiset<std::unordered_multiset<key, hash, pred, alloc>> : std::true_type {};
        
        template <typename key, typename hash, typename pred, typename alloc, typename new_type>
        struct substitute<std::unordered_multiset<key, hash, pred, alloc>, new_type> {
            using type = std::unordered_multiset<new_type>;
        };
        
        template <typename type>
        struct is_initializer_list : std::false_type {};
        template <typename type>
        struct is_initializer_list<std::initializer_list<type>> : std::true_type {};
        
        template <typename type>
        struct is_kind_of_map : template_disjunction<
            is_map,
            is_multimap,
            is_unordered_map,
            is_unordered_multimap
        >::template eval<type> {};
        
        template <typename type>
        struct is_kind_of_set : template_disjunction<
            is_set,
            is_multiset,
            is_unordered_set,
            is_unordered_multiset
        >::template eval<type> {};

        template <typename type>
        struct is_container : template_disjunction<
            is_bitset,
            is_array,
            is_vector,
            is_deque,
            is_forward_list,
            is_list,
            is_kind_of_map,
            is_kind_of_set,
            is_initializer_list
        >::template eval<type> {};

        template <typename container>
        struct container_traits {
            using tag = container_type_tag;
            static constexpr tag container_type
                = is_bitset<container>::value             ? tag::bitset
                : is_array<container>::value              ? tag::array
                : is_vector<container>::value             ? tag::vector
                : is_deque<container>::value              ? tag::deque
                : is_forward_list<container>::value       ? tag::forward_list
                : is_list<container>::value               ? tag::list
                : is_map<container>::value                ? tag::map
                : is_multimap<container>::value           ? tag::multimap
                : is_unordered_map<container>::value      ? tag::unordered_map
                : is_unordered_multimap<container>::value ? tag::unordered_multimap
                : is_set<container>::value                ? tag::set
                : is_multiset<container>::value           ? tag::multiset
                : is_unordered_set<container>::value      ? tag::unordered_set
                : is_unordered_multiset<container>::value ? tag::unordered_multiset
                : tag::not_container;
            
            template <typename new_type>
            using substitute = get_type<substitute<container, new_type>>;
        };
    };
    using namespace container_info;
};
