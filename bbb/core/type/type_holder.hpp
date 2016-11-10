/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/type/type_holder.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/type/utility.hpp>
#include <bbb/core/type/integer_sequence/integer_range.hpp>
#include <bbb/core/type/logic.hpp>

namespace bbb {
    namespace type_holders {
        template <typename ... types>
        struct type_holder;

        template <>
        struct type_holder<> {};

        template <typename type, typename ... types>
        struct type_holder<type, types ...> {
            using head = type;
            using tails = type_holder<types ...>;
        };

        namespace detail {
            template <typename sequence, typename ... types>
            struct slice;

            template <std::size_t ... indices, typename ... types>
            struct slice<index_sequence<indices ...>, types ...> {
                using type = type_holder<type_at<indices, types ...> ...>;
            };
        };

        template <std::size_t from, std::size_t to, typename ... types>
        using slice = get_type<detail::slice<index_range<from, to>, types ...>>;

        namespace detail {
            template <typename holder, typename ... types>
            struct make_unique;

            template <typename ... holded_types, typename first, typename ... types>
            struct make_unique<type_holder<holded_types ...>, first, types ...> {
                template <typename rhs>
                using eq = std::is_same<first, rhs>;

                using type = get_type<conditional_t<
                    any_t<eq, holded_types ...>::value,
                    make_unique<type_holder<holded_types ...>, types ...>,
                    make_unique<type_holder<holded_types ..., first>, types ...>
                >>;
            };
            template <typename ... holded_types>
            struct make_unique<type_holder<holded_types ...>> {
                using type = type_holder<holded_types ...>;
            };
        };

        template <typename ... types>
        using make_unique = detail::make_unique<type_holder<>, types ...>;
        template <typename ... types>
        using make_unique_t = get_type<make_unique<types ...>>;

#if BBB_EXEC_UNIT_TEST
        namespace make_unique_test {
            using test1 = unit_test::assert<
                make_unique_t<int, int>,
                type_holder<int>
            >;
            using test2 = unit_test::assert<
                make_unique_t<int, char, int>,
                type_holder<int, char>
            >;
        }
#endif
    };

    using namespace type_holders;
};
