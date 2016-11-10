/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/alias.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/type/utility.hpp>

namespace bbb {
    namespace aliases {
        template <typename> struct alias;

        namespace detail {
            template<typename type_, std::size_t depth>
            struct deep_alias {
                using type = alias<deep_alias<type_, depth - 1L>>;
            };

            template <typename type_>
            struct deep_alias<type_, 0L> {
                using type = type_;
            };
        };

        template<typename type, std::size_t depth>
        using deep_alias = get_type<detail::deep_alias<type, depth>>;

        namespace detail {
            template <typename raw_type>
            struct remove_alias { using type = raw_type; };
            template <typename raw_type>
            struct remove_alias<alias<raw_type>> { using type = raw_type; };
            template <typename raw_type>
            struct remove_aliases { using type = raw_type; };
            template <typename raw_type>
            struct remove_aliases<alias<raw_type>> { using type = get_type<remove_aliases<raw_type>>; };
        };

        template <typename type>
        using remove_alias = get_type<detail::remove_alias<type>>;
        template <typename type>
        using remove_aliases = get_type<detail::remove_aliases<type>>;

        template <typename lhs, typename rhs>
        constexpr bool is_same_alias() {
            return is_same<remove_aliases<lhs>, remove_aliases<rhs>>();
        };
    };

    using namespace aliases;
};