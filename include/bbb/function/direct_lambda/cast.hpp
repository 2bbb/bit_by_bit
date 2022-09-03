/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/cast.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/function/direct_lambda/constants.hpp>
#include <bbb/function/direct_lambda/base_class.hpp>
#include <bbb/function/direct_lambda/direct_function.hpp>

#include <bbb/core.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            namespace detail {
                template <typename t>
                struct holder {};
            };

            template <typename cast_type, typename castee_type>
            struct cast_holder : direct_function<op_type::cast_holder, castee_type, detail::holder<cast_type>> {
                using direct_function<op_type::cast_holder, castee_type, detail::holder<cast_type>>::operator();
                cast_holder(castee_type v)
                : direct_function<op_type::cast_holder, castee_type, detail::holder<cast_type>>(std::tuple<castee_type, detail::holder<cast_type>>(v, {})) {};
            };

            template <typename cast_type, typename castee_type>
            cast_holder<cast_type, castee_type> cast(castee_type v) {
                return cast_holder<cast_type, castee_type>(v);
            }

            template <typename cast_type, typename castee_type>
            struct eval<op_type::cast_holder, castee_type, detail::holder<cast_type>> {
                template <typename ... arguments>
                constexpr const cast_type evaluate(const std::tuple<castee_type, detail::holder<cast_type>> &holder, arguments && ... args) const {
                    return (cast_type)(std::get<0>(holder)(std::forward<arguments>(args) ...));
                }
            };

            template <typename cast_type, typename castee_type>
            struct is_direct_function<cast_holder<cast_type, castee_type>> : std::true_type {};
        };
    };
    using function::direct_lambda::cast;
};
