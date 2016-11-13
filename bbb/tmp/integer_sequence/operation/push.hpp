/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/push.hpp
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
                template <typename integer_type, typename sequence, integer_type ... fronts>
                struct push_front;

                template <typename integer_type, integer_type ... fronts, integer_type ... backs>
                struct push_front<integer_type, integer_sequence<integer_type, backs ...>, fronts ...> {
                    using type = integer_sequence<integer_type, fronts ..., backs ...>;
                };
            };


            template <typename integer_type, typename sequence, integer_type ... fronts>
            using push_front = detail::push_front<integer_type, sequence, fronts ...>;
            template <typename integer_type, typename sequence, integer_type ... fronts>
            using push_front_t = get_type<push_front<integer_type, sequence, fronts ...>>;

            namespace detail {
                template <typename integer_type, typename sequence, integer_type ... backs>
                struct push_back;

                template <typename integer_type, integer_type ... fronts, integer_type ... backs>
                struct push_back<integer_type, integer_sequence<integer_type, fronts ...>, backs ...> {
                    using type = integer_sequence<integer_type, fronts ..., backs ...>;
                };
            };

            template <typename integer_type, typename sequence, integer_type ... backs>
            using push_back = detail::push_back<integer_type, sequence, backs ...>;
            template <typename integer_type, typename sequence, integer_type ... backs>
            using push_back_t = get_type<push_back<integer_type, sequence, backs ...>>;
        };
    };
};
