/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/utility/alias.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

namespace bbb {
    namespace tmp {
        namespace utility {
            template <typename t>
            struct alias {
                using type = t;
            };

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
            using remove_alias = detail::remove_alias<type>;
            template <typename type>
            using remove_alias_t = get_type<remove_alias<type>>;
            template <typename type>
            using remove_aliases = detail::remove_aliases<type>;
            template <typename type>
            using remove_aliases_t = get_type<remove_aliases<type>>;

            template <typename lhs, typename rhs>
            constexpr bool is_same_alias() {
                return is_same<remove_aliases_t<lhs>, remove_aliases_t<rhs>>();
            };

#if BBB_EXEC_UNIT_TEST
            namespace alias_test {
                using test1 = unit_test::assert<
                    enable_if_t<is_same_alias<alias<int>, alias<alias<int>>>()>,
                    void
                >;
                using test1 = unit_test::assert<
                    enable_if_t<!is_same_alias<alias<int>, alias<char>>()>,
                    void
                >;
            };
#endif
        };
    };
};