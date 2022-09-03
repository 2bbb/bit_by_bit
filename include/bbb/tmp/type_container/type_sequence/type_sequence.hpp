/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_sequence/type_sequence.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/logic.hpp>

namespace bbb {
    namespace tmp {
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

                template <std::size_t index>
                using at = type_at_t<index, types ...>;
            };

            template <typename sequence>
            struct is_sequence : std::false_type {};
            template <typename sequence>
            using is_sequence_t = get_type<is_sequence<sequence>>;

            template <typename ... types>
            struct is_sequence<type_sequence<types ...>> : std::true_type {};

            template <typename sequence>
            constexpr bool is_sequence_f() {
                return is_sequence_t<sequence>::value;
            }

            template <typename sequence, enable_if_t<is_sequence<sequence>::value> * = nullptr>
            constexpr bool is_null_f() {
                return sequence::size == 0;
            }

            using empty_type_sequence = type_sequence<>;
        };

        using namespace type_sequences;
    };
};
