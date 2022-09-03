/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/logic.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

namespace bbb {
    namespace tmp {
        namespace logic {
            template <bool b>
            using make_bool_type = conditional<b, std::true_type, std::false_type>;
            template <bool b>
            using make_bool_type_t = get_type<make_bool_type<b>>;

            template <typename x>
            using not_type = make_bool_type<!x::value>;
            template <typename x>
            using not_type_t = get_type<not_type<x>>;

            template <typename x, typename y>
            using and_type = make_bool_type<x::value && y::value>;
            template <typename x, typename y>
            using and_type_t = get_type<and_type<x, y>>;

            template <typename x, typename y>
            using or_type = make_bool_type<x::value || y::value>;
            template <typename x, typename y>
            using or_type_t = get_type<or_type<x, y>>;

            template <typename x, typename y>
            using xor_type = make_bool_type<x::value != y::value>;
            template <typename x, typename y>
            using xor_type_t = get_type<xor_type<x, y>>;

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

			template <typename type, typename ... types>
			struct is_in;

			template <typename needle, typename type, typename ... types>
			struct is_in<needle, type, types ...> {
				static constexpr bool value = is_same<needle, type>::value || is_in<needle, types ...>::value;
			};
			
			template <typename needle>
			struct is_in<needle> : std::false_type {};

#if BBB_EXEC_UNIT_TEST
            namespace logic_test {
                template <typename rhs>
                using eq_int = is_same<int, rhs>;

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
};
