/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/tmp/type_container/type_set/operation/push.hpp
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
            template <typename s, typename set>
            struct push {
                using type = make_type_set_t<tseq_op::push_back_t<s, set>>;
            };
            template <typename s, typename set>
            using push_t = get_type<push<s, set>>;

#if BBB_EXEC_UNIT_TEST
            namespace push_test {
                using test1 = unit_test::assert<
                    push_t<int, type_set_t<int, char>>,
                    type_set_t<int, char>
                >;
                using test2 = unit_test::assert<
                    push_t<int, type_set_t<float, char>>,
                    type_set_t<float, char, int>
                >;
            };
#endif
        };
    };
};
