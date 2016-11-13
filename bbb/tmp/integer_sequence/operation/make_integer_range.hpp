/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/integer_sequence/operation/make_integer_range.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/utility.hpp>
#include <bbb/tmp/integer_sequence/integer_sequence.hpp>
#include <bbb/tmp/integer_sequence/operation/push.hpp>

namespace bbb {
    namespace tmp {
        namespace integer_sequence_operations {
            namespace detail {
                template <typename integer_type, typename sequence, integer_type val>
                struct deferred_prepend {
                    using type = push_front_t<integer_type, get_type<sequence>, val>;
                };

                template <typename integer_type, integer_type from, integer_type to, integer_type offset = 1>
                struct make_integer_range {
                    using type = resolve_t<conditional_t<
                        from + offset < to,
                        deferred_prepend<integer_type, make_integer_range<integer_type, from + offset, to, offset>, from>,
                        defer<integer_sequence<integer_type, from>>
                    >>;
                };
            };

            template <typename integer_type, integer_type from, integer_type to, integer_type offset = 1>
            using make_integer_range = detail::make_integer_range<integer_type, from, to, offset>;
            template <typename integer_type, integer_type from, integer_type to, integer_type offset = 1>
            using make_integer_range_t = get_type<make_integer_range<integer_type, from, to, offset>>;

            template <std::size_t from, std::size_t to, std::size_t offset = 1>
            using make_index_range = make_integer_range<std::size_t, from, to, offset>;
            template <std::size_t from, std::size_t to, std::size_t offset = 1>
            using make_index_range_t = get_type<make_index_range<from, to, offset>>;

#if BBB_EXEC_UNIT_TEST
            namespace integer_range_test {
                using test1 = unit_test::assert<
                make_index_range_t<0, 4>,
                index_sequence<0, 1, 2, 3>
                >;
                using test2 = unit_test::assert<
                make_index_range_t<0, 4, 2>,
                index_sequence<0, 2>
                >;
                using test3 = unit_test::assert<
                make_index_range_t<0, 4, 3>,
                index_sequence<0, 3>
                >;
                using test4 = unit_test::assert<
                make_index_range_t<0, 4, 4>,
                index_sequence<0>
                >;
                using test5 = unit_test::assert<
                make_index_range_t<1, 4>,
                index_sequence<1, 2, 3>
                >;
            };
#endif
        };
    };
};
