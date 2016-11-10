/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/basic.hpp.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <type_traits>

namespace bbb {
    template <typename T>
    using get_type = typename T::type;

    namespace unit_test {
        template <typename expr, typename require>
        using assert = get_type<std::enable_if<
            std::is_same<expr, require>::value,
            expr
        >>;
    };
};
