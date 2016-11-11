/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/bind.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/function/direct_lambda.hpp>

namespace bbb {
    namespace binder {

        template <typename object, typename result, typename ... arguments, typename bind_arguments>
        auto bind(result(object::*meth)(arguments ...), object obj, bind_arguments ...)
        -> std::function<result(arguments ...)>
        {
            return std::bind(meth, obj, )
        };

    };
    using namespace binder;
};
