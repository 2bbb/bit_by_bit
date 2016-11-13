/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_sequence/operation/map.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp/variadic.hpp>
#include <bbb/tmp/type_container/type_sequence/type_sequence.hpp>

#if BBB_EXEC_UNIT_TEST
#   include <bbb/tmp/logic.hpp>
#endif

namespace bbb {
    namespace tmp {
        namespace type_sequence_operations {
            template <template <typename> class function, typename sequence>
            struct map;

            template <template <typename> class function, typename sequence>
            using map_t = get_type<map<function, sequence>>;

            template <template <typename> class function, typename ... types>
            struct map<function, type_sequence<types ...>> {
                using type = va_op::map_t<function, types ...>;
            };

#if BBB_EXEC_UNIT_TEST
            namespace type_sequence_map_test {
                template <typename ... ts>
                using seq = type_sequence<ts ...>;
                template <typename type> using and_true = and_type_t<std::true_type, type>;
                using test1 = unit_test::assert<
                    map_t<and_true, seq<std::true_type, std::false_type>>,
                    seq<std::true_type, std::false_type>
                >;

                template <typename type> using and_false = and_type_t<std::false_type, type>;
                using test2 = unit_test::assert<
                    map_t<and_false, seq<std::true_type, std::false_type>>,
                    seq<std::false_type, std::false_type>
                >;

                template <typename type> using or_true = or_type_t<std::true_type, type>;
                using test3 = unit_test::assert<
                    map_t<or_true, seq<std::true_type, std::false_type>>,
                    seq<std::true_type, std::true_type>
                >;
            };
#endif
        };
    };
};
