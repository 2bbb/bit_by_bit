/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/type/range.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/type/sequence.hpp>
#include <bbb/core/type/sequence_utils.hpp>

namespace bbb {
    namespace sequence_range {
        namespace detail {
            template <typename integer_type, integer_type from, integer_type to, integer_type offset = 1>
            struct integer_range {
                using back = integer_range<integer_type, from + offset, to, offset>;
                struct wrapper {
                    using type = sequence_prepend<integer_type, back, from>;
                };
                using type = get_type<conditional_t<
                    from + offset <= to,
                    wrapper,
                    back
                >>;
            };

            template <typename integer_type, integer_type n, integer_type offset>
            struct integer_range<integer_type, n, n, offset> {
                using type = integer_sequence<integer_type, n>;
            };
        };

        template <typename integer_type, integer_type from, integer_type to, integer_type offset = 1>
        using integer_range = typename detail::integer_range<integer_type, from, to, offset>::type;

        template <std::size_t from, std::size_t to, std::size_t offset = 1>
        using index_range = integer_range<std::size_t, from, to, offset>;
    };

    using namespace sequence_range;
};
