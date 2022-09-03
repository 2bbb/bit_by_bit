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

#include <bbb/function/direct_lambda/constants.hpp>
#include <bbb/function/direct_lambda/utility.hpp>
#include <bbb/function/direct_lambda/base_class.hpp>
#include <bbb/function/direct_lambda/direct_function.hpp>
#include <bbb/function/direct_lambda/value_holder.hpp>
#include <bbb/function/direct_lambda/placeholder.hpp>
#include <bbb/function/direct_lambda/type_traits.hpp>
#include <bbb/function/direct_lambda/unary_function.hpp>
#include <bbb/function/direct_lambda/binary_function.hpp>

#include <bbb/core.hpp>
#include <cmath>

namespace bbb {
    namespace function {
        namespace direct_lambda {
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

            def_std_unary_function(sqrt);
            def_std_unary_function(cbrt);
            def_std_unary_function(abs);
            def_std_unary_function(fabs);
            
            def_std_unary_function(erf);
            def_std_unary_function(erfc);
            def_std_unary_function(tgamma);
            def_std_unary_function(lgamma);

            def_std_unary_function(rint);
            def_std_unary_function(lrint);
            def_std_unary_function(llrint);
            def_std_unary_function(round);
            def_std_unary_function(floor);
            def_std_unary_function(ceil);
            def_std_unary_function(trunc);
            def_std_unary_function(nearbyint);

#undef def_std_unary_function

            def_std_binary_function(atan2);
            def_std_binary_function(ldexp);
            def_std_binary_function(frexp);
            def_std_binary_function(scalbn);
            def_std_binary_function(scalbln);
            def_std_binary_function(pow);
            def_std_binary_function(hypot);
            def_std_binary_function(fmod);
            def_std_binary_function(remainder);
            def_std_binary_function(copysign);
            def_std_binary_function(fmax);
            def_std_binary_function(fmin);
            def_std_binary_function(fdim);

#undef def_std_binary_function

            // def_std_triary_function(fma);
        }
        namespace op {
            using direct_lambda::sqrt;
            using direct_lambda::cbrt;

            using direct_lambda::sin;
            using direct_lambda::cos;
            using direct_lambda::tan;
            using direct_lambda::asin;
            using direct_lambda::acos;
            using direct_lambda::atan;
            using direct_lambda::sinh;
            using direct_lambda::cosh;
            using direct_lambda::tanh;
            using direct_lambda::asinh;
            using direct_lambda::acosh;
            using direct_lambda::atanh;

            using direct_lambda::exp;
            using direct_lambda::expm1;
            using direct_lambda::log;
            using direct_lambda::log10;
            using direct_lambda::log1p;
            using direct_lambda::ilogb;

            using direct_lambda::abs;
            using direct_lambda::rint;
            using direct_lambda::lrint;
            using direct_lambda::llrint;
            using direct_lambda::round;
            using direct_lambda::floor;
            using direct_lambda::ceil;
            using direct_lambda::trunc;
            using direct_lambda::nearbyint;
        };
    }
};
