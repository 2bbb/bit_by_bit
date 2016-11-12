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
            template <typename integer_type, integer_type from, integer_type to, integer_type offset = 1>
            struct integer_range {
                using back_sequence = integer_range<integer_type, from + offset, to, offset>;
                using type = resolve_t<conditional_t<
                    from + offset <= to,
                    defer<sequence_prepend<integer_type, get_type<back_sequence>, from>>,
                    back_sequence
                >>;
            };

            template <typename integer_type, integer_type n, integer_type offset>
            struct integer_range<integer_type, n, n, offset> {
                using type = integer_sequence<integer_type>;
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
        };
#endif
    };

    using namespace sequence_range;
};
