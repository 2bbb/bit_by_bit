/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/type/sequence/integer_sequence.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/utility.hpp>

namespace bbb {
    namespace tmp {
        namespace integer_sequences {

#if bbb_is_cpp14
            using std::integer_sequence;
            using std::make_integer_sequence;
            using std::index_sequence;
            using std::make_index_sequence;
            using std::index_sequence_for;
#else
            template <typename type, type ... ns>
            struct integer_sequence {
                using value_type = type;
                static constexpr std::size_t size() noexcept { return sizeof...(ns); }
            };

            namespace detail {
                template <typename integer_type, integer_type n, integer_type ... ns>
                struct make_integer_sequence {
                    using type = resolve_t<conditional_t<
                        n == 0,
                        defer<integer_sequence<integer_type, ns ...>>,
                        detail::make_integer_sequence<integer_type, n - 1, n - 1, ns ...>
                    >>;
                };
            };

            template <typename type, type n>
            using make_integer_sequence = detail::make_integer_sequence<type, n>;

            template <std::size_t ... ns>
            using index_sequence = integer_sequence<std::size_t, ns ...>;

            template <std::size_t n>
            using make_index_sequence = make_integer_sequence<std::size_t, n>;

            template <typename... types>
            using index_sequence_for = make_index_sequence<sizeof...(types)>;
            template <typename type, type n>
#endif

            using make_integer_sequence_t = get_type<make_integer_sequence<type, n>>;
            template <std::size_t n>
            using make_index_sequence_t = get_type<make_index_sequence<n>>;
            template <typename... types>
            using index_sequence_for_t = get_type<index_sequence_for<types ...>>;

#if BBB_EXEC_UNIT_TEST
            namespace integer_sequence_test {
                using test1 = unit_test::assert<
                    make_index_sequence_t<4>,
                    index_sequence<0, 1, 2, 3>
                >;
                using test2 = unit_test::assert<
                    index_sequence_for_t<int, int>,
                    index_sequence<0, 1>
                >;
            };
#endif
        };
        using namespace integer_sequences;
    };
};