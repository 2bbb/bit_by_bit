/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/tmp/inheritance.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/type_container/type_sequence.hpp>

namespace bbb {
    namespace tmp {
        namespace inheritance {
            template <typename holder>
            struct multiple_inheritance_impl;
            
            template <typename ... base_types>
            struct multiple_inheritance_impl<type_sequence<base_types ...>> : public base_types ... {
                using types = type_sequence<base_types ...>;
                template <std::size_t index>
                using type_at = typename types::template at<index>;
            };
            
            template <>
            struct multiple_inheritance_impl<type_sequence<>> {
                using types = type_sequence<>;
            };

            template <typename ... types>
            using multiple_inheritance = multiple_inheritance_impl<tseq_op::make_unique_t<tseq_op::flatten_t<types ...>>>;
            
            template <typename base_type, typename default_type, typename ... configs>
            struct search_inherited_type;
            template <typename base_type, typename default_type, typename ... configs>
            using search_inherited_type_t = get_type<search_inherited_type<base_type, default_type, configs ...>>;
            
            template <typename base_type, typename default_type, typename config, typename ... configs>
            struct search_inherited_type<base_type, default_type, config, configs ...> {
                using type = conditional_t<
                    std::is_base_of<base_type, config>::value,
                    config,
                    search_inherited_type_t<base_type, default_type, configs ...>
                >;
            };
            template <typename base_type, typename default_type>
            struct search_inherited_type<base_type, default_type> {
                using type = base_type;
            };

            template <typename base_type, typename default_type, typename ... configs>
            struct search_inherited_types_impl;
            template <typename base_type, typename default_type, typename ... configs>
            using search_inherited_types_impl_t = get_type<search_inherited_types_impl<base_type, default_type, configs ...>>;
            
            template <typename base_type, typename default_type, typename config, typename ... configs>
            struct search_inherited_types_impl<base_type, default_type, config, configs ...> {
                using others = search_inherited_types_impl_t<base_type, default_type, configs ...>;
                using type = conditional_t<
                    std::is_base_of<base_type, config>::value,
                    tseq_op::push_front_t<config, others>,
                    others
                >;
            };

            template <typename base_type, typename default_type>
            struct search_inherited_types_impl<base_type, default_type> {
                using type = type_sequence<>;
            };

            template <typename base_type, typename default_type, typename ... configs>
            struct search_inherited_types {
                using inherited = search_inherited_types_impl_t<base_type, default_type, configs ...>;
                using type = conditional_t<
                    inherited::size == 0,
                    type_sequence<default_type>,
                    inherited
                >;
            };

            template <typename base_type, typename default_type, typename ... configs>
            using search_inherited_types_t = get_type<search_inherited_types<base_type, default_type, configs ...>>;
        }; // namespace inheritance

        using namespace inheritance;
    }; // namespace tmp
};