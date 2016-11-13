/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/variadic/operation/map.hpp
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
        namespace variadic_operations {
            template <template <typename> class function, typename ... types>
            struct map {
                using type = type_sequence<function<types> ...>;
            };

            template <template <typename> class function, typename ... types>
            using map_t = get_type<map<function, types ...>>;

#if BBB_EXEC_UNIT_TEST
            namespace variadic_map_test {
                template <typename type> using and_true = and_type_t<std::true_type, type>;
                using test1 = unit_test::assert<
                    map_t<and_true, std::true_type, std::false_type>,
                    type_sequence<std::true_type, std::false_type>
                >;

                template <typename type> using and_false = and_type_t<std::false_type, type>;
                using test2 = unit_test::assert<
                    map_t<and_false, std::true_type, std::false_type>,
                    type_sequence<std::false_type, std::false_type>
                >;

                template <typename type> using or_true = or_type_t<std::true_type, type>;
                using test3 = unit_test::assert<
                    map_t<or_true, std::true_type, std::false_type>,
                    type_sequence<std::true_type, std::true_type>
                >;
            };
#endif
        };
    };
};