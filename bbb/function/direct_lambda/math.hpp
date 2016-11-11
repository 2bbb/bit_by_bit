/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/math.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <cmath>

#include <bbb/core.hpp>
#include <bbb/function/direct_lambda/constants.hpp>
#include <bbb/function/direct_lambda/utility.hpp>
#include <bbb/function/direct_lambda/base_class.hpp>
#include <bbb/function/direct_lambda/function.hpp>
#include <bbb/function/direct_lambda/value_holder.hpp>
#include <bbb/function/direct_lambda/placeholder.hpp>
#include <bbb/function/direct_lambda/type_traits.hpp>
#include <bbb/function/direct_lambda/unary_function.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            def_std_unary_function(sqrt);
            def_std_unary_function(cbrt);

            def_std_unary_function(sin);
            def_std_unary_function(cos);
            def_std_unary_function(tan);
            def_std_unary_function(asin);
            def_std_unary_function(acos);
            def_std_unary_function(atan);
            def_std_unary_function(sinh);
            def_std_unary_function(cosh);
            def_std_unary_function(tanh);
            def_std_unary_function(asinh);
            def_std_unary_function(acosh);
            def_std_unary_function(atanh);

            def_std_unary_function(exp);
            def_std_unary_function(expm1);
            def_std_unary_function(log);
            def_std_unary_function(log10);
            def_std_unary_function(log1p);
            def_std_unary_function(ilogb);

            def_std_unary_function(abs);
            def_std_unary_function(rint);
            def_std_unary_function(lrint);
            def_std_unary_function(llrint);
            def_std_unary_function(round);
            def_std_unary_function(floor);
            def_std_unary_function(ceil);
            def_std_unary_function(trunc);
            def_std_unary_function(nearbyint);
        }
    }
};
