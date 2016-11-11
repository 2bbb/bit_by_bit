/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/type/logic.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/tmp/traits.hpp>

namespace bbb {
    namespace logic {
        template <bool b>
        using bool_type = conditional_t<b, std::true_type, std::false_type>;

        template <typename x, typename y>
        using not_type = bool_type<!x::value>;

        template <typename x, typename y>
        using and_type = bool_type<x::value && y::value>;

        template <typename x, typename y>
        using or_type = bool_type<x::value || y::value>;

        template <typename x, typename y>
        using xor_type = bool_type<x::value != y::value>;

        namespace detail {
            template <template <typename> class pred, typename ... arguments>
            struct all;
            template <template <typename> class pred, typename argument, typename ... arguments>
            struct all<pred, argument, arguments ...> {
                using type = typename std::conditional<
                    pred<argument>::value,
                    typename all<pred, arguments ...>::type,
                    std::false_type
                >::type;
            };
            template <template <typename> class pred>
            struct all<pred> {
                using type = std::true_type;
            };

            template <template <typename> class pred, typename ... arguments>
            struct any;
            template <template <typename> class pred, typename argument, typename ... arguments>
            struct any<pred, argument, arguments ...> {
                using type = typename std::conditional<
                    pred<argument>::value,
                    std::true_type,
                    typename any<pred, arguments ...>::type
                >::type;
            };
            template <template <typename> class pred>
            struct any<pred> {
                using type = std::false_type;
            };
        };

        template <template <typename> class pred, typename ... arguments>
        using all = detail::all<pred, arguments ...>;
        template <template <typename> class pred, typename ... arguments>
        using all_t = get_type<all<pred, arguments ...>>;

        template <template <typename> class pred, typename ... arguments>
        using any = detail::any<pred, arguments ...>;
        template <template <typename> class pred, typename ... arguments>
        using any_t = get_type<any<pred, arguments ...>>;

#if BBB_EXEC_UNIT_TEST
        namespace logic_test {
            template <typename rhs>
            using eq_int = std::is_same<int, rhs>;

            using test1 = unit_test::assert<
                all_t<eq_int, int, float>,
                std::false_type
            >;
            using test2 = unit_test::assert<
                all_t<eq_int, int, int>,
                std::true_type
            >;
            using test3 = unit_test::assert<
                any_t<eq_int, int, int>,
                std::true_type
            >;
            using test4 = unit_test::assert<
                any_t<eq_int, int, float>,
                std::true_type
            >;
            using test5 = unit_test::assert<
                any_t<eq_int, char, float>,
                std::false_type
            >;
        }
#endif
    };

    using namespace logic;
};
