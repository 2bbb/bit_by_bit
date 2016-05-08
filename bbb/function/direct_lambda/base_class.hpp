/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/base_class.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            template <op_type op, typename ... holders>
            struct eval;

            template <op_type op, typename ... holders>
            struct function {
                std::tuple<holders ...> holder;

                template <typename ... arguments>
                constexpr auto operator()(arguments && ... args) const
                    -> decltype((eval<op, holders ...>()).evaluate(holder, std::forward<arguments>(args) ...))
                {
                    return (eval<op, holders ...>()).evaluate(holder, std::forward<arguments>(args) ...);
                }
            };

            struct null_value {};
        };
    };
};