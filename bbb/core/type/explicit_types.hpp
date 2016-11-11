/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/type/explicit_types.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/tmp/traits.hpp>

namespace bbb {
    namespace explicit_types {
        template <typename type_>
        struct explicit_type {
            using type = type_;
            explicit_type() = default;
            explicit_type(const type &t)
                : t(t) {};
            explicit_type(type &&t)
                : t(std::forward<type>(t)) {};

            template <typename _>
            explicit_type(_) = delete;

            operator type&() { return t; };
            operator const type &() const { return t; };
            const type &get() const { return t; };

        private:
            type t;
        };

        using explicit_bool = explicit_type<bool>;
    };
    using namespace explicit_types;
};
