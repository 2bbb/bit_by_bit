/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/type/sequence/sequence_operation.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/tmp/integer_sequence/integer_sequence.hpp>

namespace bbb {
    namespace sequence_utils {
        namespace detail {
            template <typename sequence1, typename sequence2, typename ... sequences>
            struct sequence_cat;
            
            template <typename integer_type, integer_type ... indices1, integer_type ... indices2, typename sequence, typename ... sequences>
            struct sequence_cat<
                integer_sequence<integer_type, indices1 ...>,
                integer_sequence<integer_type, indices2 ...>,
                sequence,
                sequences ...
            > {
                using type = get_type<sequence_cat<integer_sequence<integer_type, indices1 ..., indices2 ...>, sequence, sequences ...>>;
            };
            
            template <typename integer_type, integer_type ... indices1, integer_type ... indices2>
            struct sequence_cat<
                integer_sequence<integer_type, indices1 ...>,
                integer_sequence<integer_type, indices2 ...>
            > {
                using type = integer_sequence<integer_type, indices1 ..., indices2 ...>;
            };
        };
        
        template <typename ... sequences>
        using sequence_cat = get_type<detail::sequence_cat<sequences ...>>;
        
        namespace detail {
            template <typename integer_type, typename sequence, integer_type ... fronts>
            struct sequence_prepend;
            
            template <typename integer_type, integer_type ... fronts, integer_type ... backs>
            struct sequence_prepend<integer_type, integer_sequence<integer_type, backs ...>, fronts ...> {
                using type = integer_sequence<integer_type, fronts ..., backs ...>;
            };
        };
        
        template <typename integer_type, typename sequence, integer_type ... fronts>
        using sequence_prepend = get_type<detail::sequence_prepend<integer_type, sequence, fronts ...>>;
        
        namespace detail {
            template <typename integer_type, typename sequence, integer_type ... backs>
            struct sequence_append;
            
            template <typename integer_type, integer_type ... fronts, integer_type ... backs>
            struct sequence_append<integer_type, integer_sequence<integer_type, fronts ...>, backs ...> {
                using type = integer_sequence<integer_type, fronts ..., backs ...>;
            };
        };
        
        template <typename integer_type, typename sequence, integer_type ... backs>
        using sequence_append = get_type<detail::sequence_append<integer_type, sequence, backs ...>>;
    };
    using namespace sequence_utils;
};
