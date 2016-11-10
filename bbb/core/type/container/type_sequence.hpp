/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/type/container/type_holder.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/type/utility.hpp>
#include <bbb/core/type/integer_sequence/integer_range.hpp>
#include <bbb/core/type/logic.hpp>

namespace bbb {
    namespace type_sequences {
        template <typename ... types>
        struct type_sequence;

        template <>
        struct type_sequence<> {};

        template <typename type, typename ... types>
        struct type_sequence<type, types ...> {
            using head = type;
            using tails = type_sequence<types ...>;
        };
    };

    using namespace type_sequences;
};
