/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * lambda_utils.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include "constants.hpp"
#include "type_utils.hpp"

#include <functional>

namespace bbb {
    namespace curry {
        template <typename T, typename U>
        U extraction(T *t, U (T::*method_ptr)()) {
            return t->method_ptr();
        };

        template <typename Function, typename ResultFunction, typename T, typename U, typename ... Args>
        ResultFunction bind(Function f, U (T::*method_ptr)(), Args & ... args) {
            return std::bind(f, extraction(std::placeholders::_1, method_ptr), args ...);
        }
    };
};