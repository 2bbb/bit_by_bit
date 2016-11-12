/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/type/sequence/integer_range.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/tmp/traits.hpp>
#include <bbb/core/tmp/utility.hpp>
#include <bbb/core/tmp/integer_sequence/integer_sequence.hpp>
#include <bbb/core/tmp/integer_sequence/sequence_operation.hpp>

namespace bbb {
    namespace sequence_range {
        namespace detail {
            template <typename integer_type, typename sequence, integer_type val>
            struct deferred_prepend {
                using type = sequence_prepend_t<integer_type, get_type<sequence>, val>;
            };

            template <typename integer_type, integer_type from, integer_type to, integer_type offset = 1>
            struct integer_range {
                using type = resolve_t<conditional_t<
                    from + offset < to,
                    deferred_prepend<integer_type, integer_range<integer_type, from + offset, to, offset>, from>,
                    defer<integer_sequence<integer_type, from>>
                >>;
            };
        };

        template <typename integer_type, integer_type from, integer_type to, integer_type offset = 1>
        using integer_range = detail::integer_range<integer_type, from, to, offset>;
        template <typename integer_type, integer_type from, integer_type to, integer_type offset = 1>
        using integer_range_t = get_type<integer_range<integer_type, from, to, offset>>;

        template <std::size_t from, std::size_t to, std::size_t offset = 1>
        using index_range = integer_range<std::size_t, from, to, offset>;
        template <std::size_t from, std::size_t to, std::size_t offset = 1>
        using index_range_t = get_type<index_range<from, to, offset>>;

#ifdef BBB_EXEC_UNIT_TEST
        namespace integer_range_test {
            using test1 = unit_test::assert<
                index_range_t<0, 4>,
                index_sequence<0, 1, 2, 3>
            >;
            using test2 = unit_test::assert<
                index_range_t<0, 4, 2>,
                index_sequence<0, 2>
            >;
            using test3 = unit_test::assert<
                index_range_t<0, 4, 3>,
                index_sequence<0, 3>
            >;
            using test4 = unit_test::assert<
                index_range_t<0, 4, 4>,
                index_sequence<0>
            >;
            using test5 = unit_test::assert<
                index_range_t<1, 4>,
                index_sequence<1, 2, 3>
            >;
        };
#endif
    };

    using namespace sequence_range;
};
