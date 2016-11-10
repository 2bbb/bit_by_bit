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
        struct type_sequence<> {
            static constexpr std::size_t size = 0;
        };

        template <typename type, typename ... types>
        struct type_sequence<type, types ...> {
            using head = type;
            using tails = type_sequence<types ...>;
            static constexpr std::size_t size = sizeof...(types) + 1;
        };

        namespace detail {
            template <typename sequence>
            struct is_sequence : std::false_type {};

            template <typename ... types>
            struct is_sequence<type_sequence<types ...>> : std::true_type {};
        }

        template <typename sequence>
        constexpr bool is_sequence() {
            return detail::is_sequence<sequence>::value;
        }

        template <typename sequence, typename std::enable_if<is_sequence<sequence>()>::type * = nullptr>
        constexpr bool is_null() {
            return sequence::size == 0;
        }
    };

    using namespace type_sequences;
};
