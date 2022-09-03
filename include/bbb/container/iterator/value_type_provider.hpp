/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/container/iterator/value_type_provider.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <iterator>

#include <bbb/core.hpp>

#include <bbb/container/iterator/traits.hpp>

namespace bbb {
    namespace container {
        namespace iterator {
            template <typename container, bool has_iterator = iteratable_class_traits<container>::has_iterator>
            struct value_type_provider {};

            template <typename container>
            struct value_type_provider<container, true> {
                using value_type = typename std::iterator_traits<typename container::iterator>::value_type;
            };
        };
    };
};
