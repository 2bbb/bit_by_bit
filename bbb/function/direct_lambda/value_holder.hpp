/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/value_holder.hpp
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
            template <typename value_t>
            struct value_holder {
                value_holder(value_t &v) : v(v) {};
                template <typename ... arguments>
                constexpr value_t& operator()(arguments && ...) const { return v; }
            private:
                value_t &v;
            };

            template <typename value_t>
            struct const_value_holder {
                const_value_holder(const value_t &v) : v(v) {};
                template <typename ... arguments>
                constexpr const value_t& operator()(arguments && ...) const { return v; }
            private:
                const value_t &v;
            };
        };
    };
};
