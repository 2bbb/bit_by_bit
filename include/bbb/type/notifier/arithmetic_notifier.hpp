/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/type/notifier/arithmetic_notifier.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#ifndef bbb_type_notifier_arithmetic_notifier_hpp
#define bbb_type_notifier_arithmetic_notifier_hpp

#include <functional>

namespace bbb {
    namespace notifiers {
        template <typename type>
        struct arithmetic_notifier {
            arithmetic_notifier()
                : value(type()) {}
            arithmetic_notifier(type value)
                : value(value) {}

            arithmetic_notifier(std::function<void(type)> will_change,
                                std::function<void(type)> did_change)
                : will_change(will_change)
                , did_change(did_change) {}

            arithmetic_notifier(const arithmetic_notifier &mom) = default;
            arithmetic_notifier(arithmetic_notifier &&mom) = default;

            arithmetic_notifier &operator=(const arithmetic_notifier &mom) = default;
            arithmetic_notifier &operator=(arithmetic_notifier &&mom) = default;

            operator type &() { return value; }
            operator const type &() const { return value; }

            template <typename T>
            arithmetic_notifier &operator=(T value) {
                will_change(this->value);
                this->value = value;
                did_change(this->value);
                return *this;
            }

            arithmetic_notifier &operator++() {
                will_change(this->value);
                ++value;
                did_change(this->value);
                return *this;
            }

            arithmetic_notifier operator++(int) {
                arithmetic_notifier tmp = *this;
                will_change(this->value);
                value++;
                did_change(this->value);
                return tmp;
            }

            arithmetic_notifier &operator--() {
                will_change(this->value);
                --value;
                did_change(this->value);
                return *this;
            }

            arithmetic_notifier operator--(int) {
                arithmetic_notifier tmp = *this;
                will_change(this->value);
                value--;
                did_change(this->value);
                return tmp;
            }

#define def_op(op)\
            template <typename T>\
            arithmetic_notifier &operator op(T value) {\
                will_change(this->value);\
                this->value op value;\
                did_change(this->value);\
                return *this;\
            }

            def_op(+=);
            def_op(-=);
            def_op(*=);
            def_op(/=);
            def_op(%=);
            def_op(&=);
            def_op(|=);
            def_op(^=);
            def_op(<<=);
            def_op(>>=);

#undef def_op

            inline void notify_will_change() { will_change(this->value); }
            inline void notify_did_change() { did_change(this->value); }
            void value_will_change(std::function<void(type)> callback) {
                will_change = callback;
            }
            void value_did_change(std::function<void(type)> callback) {
                did_change = callback;
            }
        private:
            type value;
            std::function<void(type)> will_change{[](type){}};
            std::function<void(type)> did_change{[](type){}};
        };
    };
};


#endif /* bbb_type_notifier_arithmetic_notifier_hpp */
