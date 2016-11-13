/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/type/notifier.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#ifndef bbb_type_notifier_hpp
#define bbb_type_notifier_hpp

#include <bbb/core.hpp>

#include <bbb/type/notifier/arithmetic_notifier.hpp>
#include <bbb/type/notifier/referenced_arithmetic_notifier.hpp>
#include <bbb/type/notifier/string_notifier.hpp>

namespace bbb {
    namespace notifiers {
        namespace detail {
            template <typename, typename = void>
            struct notifier;

            template <typename type_>
            struct notifier<type_, enable_if_t<is_number_f<type_>()>> {
                using type = arithmetic_notifier<type_>;
            };

            template <typename type_>
            struct notifier<type_, enable_if_t<is_basic_string<type_>::value>> {
                using type = string_notifier<type_>;
            };
        };
        template <typename type>
        using notifier = get_type<detail::notifier<type>>;
    };

    using notifiers::notifier;
};

#endif /* bbb_type_notifier_hpp */
