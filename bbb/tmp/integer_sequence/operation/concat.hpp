/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/concat_sequence.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/tmp/integer_sequence/integer_sequence.hpp>

namespace bbb {
    namespace tmp {
        namespace integer_sequence_operations {
            namespace detail {
                template <typename sequence1, typename sequence2, typename ... sequences>
                struct concat;

                template <typename integer_type, integer_type ... indices1, integer_type ... indices2, typename sequence, typename ... sequences>
                struct concat<
                    integer_sequence<integer_type, indices1 ...>,
                    integer_sequence<integer_type, indices2 ...>,
                    sequence,
                    sequences ...
                > {
                        using type = get_type<concat<integer_sequence<integer_type, indices1 ..., indices2 ...>, sequence, sequences ...>>;
                };

                template <typename integer_type, integer_type ... indices1, integer_type ... indices2>
                struct concat<
                    integer_sequence<integer_type, indices1 ...>,
                    integer_sequence<integer_type, indices2 ...>
                > {
                    using type = integer_sequence<integer_type, indices1 ..., indices2 ...>;
                };
            };

            template <typename ... sequences>
            using concat = detail::concat<sequences ...>;
            template <typename ... sequences>
            using concat_t = get_type<concat<sequences ...>>;
        };
    };
};
