/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/basic.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/constants.hpp>

#include <type_traits>

namespace bbb {
    template <typename T>
    using get_type = typename T::type;

#if BBB_EXEC_UNIT_TEST
    namespace unit_test {
        template <typename expr, typename require>
        using assert = get_type<std::enable_if<
            std::is_same<expr, require>::value,
            expr
        >>;
    };
#endif
};
