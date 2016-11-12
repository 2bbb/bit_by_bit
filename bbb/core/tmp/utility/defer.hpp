/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/tmp/utility/defer.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/tmp/traits/type_traits.hpp>

namespace bbb {
    template <typename t>
    struct defer {
        using type = t;
    };

    template <bool b, typename t, typename f>
    using defered_conditional = conditional_t<b, defer<t>, defer<f>>;

    template <typename t>
    using resolve_t = get_type<t>;
};