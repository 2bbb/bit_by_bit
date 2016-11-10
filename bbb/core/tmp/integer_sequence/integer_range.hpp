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
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/tmp/traits.hpp>
#include <bbb/core/tmp/integer_sequence/integer_sequence.hpp>
#include <bbb/core/tmp/integer_sequence/sequence_operation.hpp>

namespace bbb {
    namespace sequence_range {
        namespace detail {
            template <typename integer_type, integer_type from, integer_type to, integer_type offset = 1>
            struct integer_range {
                using back_sequence = integer_range<integer_type, from + offset, to, offset>;
                struct wrapper {
                    using type = sequence_prepend<integer_type, get_type<back_sequence>, from>;
                };
                using type = get_type<conditional_t<
                    from + offset <= to,
                    wrapper,
                    back_sequence
                >>;
            };

            template <typename integer_type, integer_type n, integer_type offset>
            struct integer_range<integer_type, n, n, offset> {
                using type = integer_sequence<integer_type, n>;
            };
        };

        template <typename integer_type, integer_type from, integer_type to, integer_type offset = 1>
        using integer_range = get_type<detail::integer_range<integer_type, from, to, offset>>;

        template <std::size_t from, std::size_t to, std::size_t offset = 1>
        using index_range = integer_range<std::size_t, from, to, offset>;
    };

    using namespace sequence_range;
};
