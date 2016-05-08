/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/lambda_symbol.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

namespace bbb {
    namespace function {
        namespace lambda_symbol {
            namespace detail {
                template <typename server>
                struct subscript {
                private:
                    const server &cont;
                public:
                    subscript(const server &cont) : cont(cont) {};
                    template <typename subscript>
                    constexpr auto operator()(subscript &&index) const -> decltype(cont[index]) { return cont[index]; };
                };

                template <typename callee>
                struct apply {
                private:
                    const callee &f;
                public:
                    apply(const callee &f) : f(f) {};
                    template <typename ... arguments>
                    constexpr auto operator()(arguments && ... args) const -> decltype(f(args ...)) { return f(args ...); };
                };

                struct call {
                    template <typename callee>
                    constexpr auto operator()(callee &f) const -> decltype(f()) { return f(); }
                };
                struct bnot_op {
                    template <typename value_type>
                    constexpr auto operator()(const value_type &v) const -> decltype(~v) { return ~v; }
                };
                struct lnot_op {
                    template <typename value_type>
                    constexpr auto operator()(const value_type &v) const -> decltype(!v) { return !v; }
                };
                struct pre_inc_op {
                    template <typename value_type>
                    constexpr auto operator()(value_type &v) const -> decltype(++v) { return v; }
                };
                struct post_inc_op {
                    template <typename value_type>
                    constexpr auto operator()(value_type &v) const -> decltype(v++) { return v++; }
                };
                struct pre_dec_op {
                    template <typename value_type>
                    constexpr auto operator()(value_type &v) const -> decltype(--v) { return v; }
                };
                struct post_dec_op {
                    template <typename value_type>
                    constexpr auto operator()(value_type &v) const -> decltype(v--) { return v--; }
                };
            };

            constexpr struct {
                template <typename T>
                detail::subscript<T> operator[](const T &t) const { return detail::subscript<T>(t); }
                template <typename T>
                detail::apply<T> operator()(const T &t) const { return detail::apply<T>(t); }

                detail::call operator()() const { return {}; }
                detail::bnot_op operator~() const { return {}; }
                detail::lnot_op operator!() const { return {}; }
                detail::pre_inc_op operator++() const { return {}; }
                detail::post_inc_op operator++(int) const { return {}; }
                detail::pre_dec_op operator--() const { return {}; }
                detail::post_dec_op operator--(int) const { return {}; }
            } lambda{};

#define def_left_op(op, name)\
            namespace detail {\
                template <typename L>\
                struct left_##name {\
                private:\
                    const L &lhs;\
                public:\
                    left_##name(const L &lhs) : lhs(lhs) {}\
                    template <typename R>\
                    constexpr auto operator()(const R & rhs) const -> decltype(lhs op rhs) { return lhs op rhs; };\
                };\
            };\
            template <typename L>\
            constexpr detail::left_##name<L> operator op(const L &lhs, const decltype(lambda) &) {\
                return detail::left_##name<L>(lhs);\
            };

#define def_right_op(op, name)\
            namespace detail {\
                template <typename R>\
                struct right_##name {\
                private:\
                    const R &rhs;\
                public:\
                    right_##name(const R &rhs) : rhs(rhs) {}\
                    template <typename L>\
                    constexpr auto operator()(const L & lhs) const -> decltype(lhs op rhs) { return lhs op rhs; };\
                };\
            };\
            template <typename R>\
            constexpr detail::right_##name<R> operator op(const decltype(lambda) &, const R &rhs) {\
                return detail::right_##name<R>(rhs);\
            };

#define def_op(op, name)\
            def_left_op(op, name);\
            def_right_op(op, name);

            def_op(==, eq);
            def_op(!=, neq);
            def_op(<, lt);
            def_op(<=, lte);
            def_op(>, gt);
            def_op(>=, gte);

            def_op(&&, land);
            def_op(||, lor);

            def_op(+, plus);
            def_op(-, minus);
            def_op(*, mult);
            def_op(/, div);
            def_op(%, mod);

            def_op(&, band);
            def_op(|, bor);
            def_op(^, bxor);
            def_op(<<, lshift);
            def_op(>>, rshift);

#undef def_op
#undef def_left_op
#undef def_right_op

#define def_destructive_left_op(op, name)\
            namespace detail {\
                template <typename L>\
                struct left_##name {\
                private:\
                    L &lhs;\
                public:\
                    left_##name(L &lhs) : lhs(lhs) {}\
                    template <typename R>\
                    constexpr auto operator()(const R & rhs) const -> decltype(lhs op rhs) { return lhs op rhs; };\
                };\
            };\
            template <typename L>\
            constexpr detail::left_##name<L> operator op(L &lhs, const decltype(lambda) &) {\
                return detail::left_##name<L>(lhs);\
            };

#define def_destructive_right_op(op, name)\
            namespace detail {\
                template <typename R>\
                struct right_##name {\
                private:\
                    const R &rhs;\
                public:\
                    right_##name(const R &rhs) : rhs(rhs) {}\
                    template <typename L>\
                    constexpr auto operator()(L & lhs) const -> decltype(lhs op rhs) { return lhs op rhs; };\
                };\
            };\
            template <typename R>\
            constexpr detail::right_##name<R> operator op(const decltype(lambda) &, const R &rhs) {\
                return detail::right_##name<R>(rhs);\
            };

#define def_destructive_op(op, name)\
            def_destructive_left_op(op, name);\
            def_destructive_right_op(op, name);

            def_destructive_op(&=, band_eq);
            def_destructive_op(|=, bor_eq);
            def_destructive_op(^=, bxor_eq);

            def_destructive_op(+=, plus_eq);
            def_destructive_op(-=, miuns_eq);
            def_destructive_op(*=, mult_eq);
            def_destructive_op(/=, div_eq);
            def_destructive_op(%=, mod_eq);

            def_destructive_op(<<=, lshift_eq);
            def_destructive_op(>>=, rshift_eq);
        };

        using namespace lambda_symbol;
    };
};

#define bbb_use_lambda_symbol(sym) decltype(bbb::function::lambda) & sym = bbb::function::lambda;
