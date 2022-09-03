/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/logger/detail/flatten.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>
#include <bbb/tmp/type_container/type_sequence/operation/concat.hpp>

namespace bbb {
    namespace tmp {
        namespace type_sequence_operations {
            template <typename ... holders>
			struct flatten;
			template <typename ... holders>
			using flatten_t = get_type<flatten<holders ...>>;

			template <typename holder, typename ... holders>
			struct flatten<holder, holders ...> {
				using first = conditional_t<
					is_sequence<holder>::value,
					flatten_t<holder>,
					type_sequence<holder>
				>;
				using type = concat_t<first, flatten_t<holders ...>>;
			};

			template <typename ... holded>
			struct flatten<type_sequence<holded ...>> {
				using type = flatten_t<holded ...>;
			};

			template <typename non_holded>
			struct flatten<non_holded> {
				using type = type_sequence<non_holded>;
			};

			template <>
			struct flatten<> {
				using type = type_sequence<>;
			};
        };
    };
};