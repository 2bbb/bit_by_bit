/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_set/operation/remove.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

#include <bbb/tmp/type_container/type_set/type_set.hpp>

namespace bbb {
    namespace tmp {
        namespace type_set_operations {
            template <typename t, typename set>
            struct remove {
                using type = make_type_set_t<tseq_op::remove_all_t<t, set>>;
            };

            template <typename t, typename set>
            using remove_t = get_type<remove<t, set>>;

#if BBB_EXEC_UNIT_TEST
            namespace remove_test {
                using test1 = unit_test::assert<
                    remove_t<int, type_set_t<int, char>>,
                    type_set_t<char>
                >;
                using test2 = unit_test::assert<
                    remove_t<int, type_set_t<float, char>>,
                    type_set_t<float, char>
                >;
            };
#endif
        };
    };
};