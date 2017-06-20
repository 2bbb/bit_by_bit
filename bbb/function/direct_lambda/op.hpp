/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/op.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/function/direct_lambda/constants.hpp>
#include <bbb/function/direct_lambda/utility.hpp>
#include <bbb/function/direct_lambda/base_class.hpp>
#include <bbb/function/direct_lambda/direct_function.hpp>
#include <bbb/function/direct_lambda/value_holder.hpp>
#include <bbb/function/direct_lambda/placeholder.hpp>
#include <bbb/function/direct_lambda/type_traits.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
#define def_eval(op, name)\
            template <typename lhs, typename rhs>\
            struct eval<op_type::name, lhs, rhs> {\
                template <typename ... arguments>\
                constexpr auto evaluate(const std::tuple<lhs, rhs> &holder, arguments && ... args) const\
                -> decltype((std::get<0>(holder))(args ...) op (std::get<1>(holder))(args ...))\
                { return (std::get<0>(holder))(args ...) op (std::get<1>(holder))(args ...); }\
            };

#define def_bin_op(op, name)\
            template <typename lhs, typename rhs>\
            auto operator op(const lhs &l, const rhs &r)\
            -> type_enable_if_t<\
                conjunction<is_direct_lambdable<lhs>, is_direct_lambdable<rhs>>,\
                direct_function<\
                    op_type::name,\
                    get_type<wrap_const_value_type<lhs>>,\
                    get_type<wrap_const_value_type<rhs>>\
                >\
            > {\
                return {std::tuple<get_type<wrap_const_value_type<lhs>>, get_type<wrap_const_value_type<rhs>>>(l, r)};\
            };

#define def_op(op, name)\
            def_eval(op, name)\
            def_bin_op(op, name)

            def_op(==, eq);
            def_op(!=, neq);

            def_op(<, lt);
            def_op(<=, lte);
            def_op(>, gt);
            def_op(>=, gte);

            def_op(+, add);
            def_op(-, sub);
            def_op(*, mul);
            def_op(/, div);
            def_op(%, mod);

            def_op(&&, land);
            def_op(||, lor);
            def_op(&, band);
            def_op(|, bor);
            def_op(^, bxor);
#undef def_op
#undef def_bin_op
#undef def_eval
        };
    };
};
