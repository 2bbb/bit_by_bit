/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_sequence/operation/apply.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>

namespace bbb {
    namespace tmp {
        namespace type_sequence_operations {
            template <template <typename ...> class func, typename sequence, typename ... other_args>
            struct apply;
            template <template <typename ...> class func, typename sequence, typename ... other_args>
            using apply_t = get_type<apply<func, sequence>>;

            template <template <typename ...> class func, typename ... ts, typename ... other_args>
            struct apply<func, type_sequence<ts ...>, other_args ...> {
                using type = func<other_args ..., ts ...>;
            };
        };
    };
};