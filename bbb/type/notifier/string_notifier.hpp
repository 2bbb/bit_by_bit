/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/type/notifier/string_notifier.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#ifndef bbb_type_notifier_string_notifier_hpp
#define bbb_type_notifier_string_notifier_hpp

#include <functional>
#include <iterator>
#include <string>
#include <initializer_list>

#include <bbb/type/notifier/referenced_arithmetic_notifier.hpp>

namespace bbb {
    namespace notifiers {
        namespace detail {
            template <typename>
            struct is_basic_string { static constexpr bool value = false; };

            template <typename character_type, typename traits, typename alloc>
            struct is_basic_string<std::basic_string<character_type, traits, alloc>> { static constexpr bool value = true; };
        };

        template <typename>
        struct string_notifier;

        template <typename character_type, typename traits, typename alloc>
        struct string_notifier<std::basic_string<character_type, traits, alloc>> : public std::basic_string<character_type, traits, alloc> {
            using type = std::basic_string<character_type>;
            using size_type = typename type::size_type;
            static constexpr size_type npos = type::npos;

            string_notifier()
                : type("") {}

            string_notifier(const string_notifier &) = default;

            template <typename T>
            string_notifier(const T &value)
                : type(value) {}

            string_notifier(string_notifier &&) = default;

            template <typename T>
            string_notifier(T &&value)
                : type(std::move(value)) {}

            string_notifier &operator=(const string_notifier &str) = default;

            template <typename T>
            string_notifier &operator=(const T &str) {
                will_change(*this);
                this->type::operator=(str);
                did_change(*this);
                return *this;
            }

            string_notifier &operator=(string_notifier &&str) = default;

            template <typename T>
            string_notifier &operator=(T &&str) {
                will_change(*this);
                this->type::operator=(std::move(str));
                did_change(*this);
                return *this;
            }

            const character_type &operator[](typename type::size_type pos) const noexcept {
                return this->type::operator[](pos);
            }
            referenced_arithmetic_notifier<character_type> operator[](typename type::size_type pos) noexcept {
                referenced_arithmetic_notifier<character_type> c(this->type::operator[](pos));
                c.value_will_change([this](character_type) { notify_will_change(); });
                c.value_did_change([this](character_type) { notify_did_change(); });
                return c;
            }
            const character_type &at(typename type::size_type pos) const {
                return this->type::at(pos);
            }
            referenced_arithmetic_notifier<character_type> at(typename type::size_type pos) {
                referenced_arithmetic_notifier<character_type> c(this->type::at(pos));
                c.value_will_change([this](character_type) { notify_will_change(); });
                c.value_did_change([this](character_type) { notify_did_change(); });
                return c;
            }

#define def_accessor(accessor)\
            const character_type &accessor() const {\
                return this->type::accessor();\
            }\
            referenced_arithmetic_notifier<character_type> accessor() {\
                referenced_arithmetic_notifier<character_type> c(this->type::accessor());\
                c.value_will_change([this](character_type) { notify_will_change(); });\
                c.value_did_change([this](character_type) { notify_did_change(); });\
                return c;\
            }

            def_accessor(front);
            def_accessor(back);

#undef def_accessor

            using inner_iterator = typename type::iterator;
            using inner_const_iterator = typename type::const_iterator;
            struct iterator : public inner_iterator {
                friend string_notifier;
                using iterator_traits = std::iterator_traits<inner_iterator>;

                using iterator_category = typename iterator_traits::iterator_category;
                using inner_value_type = typename iterator_traits::value_type;
                using value_type = referenced_arithmetic_notifier<inner_value_type>;
                using reference = value_type;
                using difference_type = typename iterator_traits::difference_type;
                using pointer = typename iterator_traits::pointer;

                iterator()
                    : parent(nullptr) {}

                iterator(inner_iterator it, string_notifier *parent)
                    : inner_iterator(it)
                    , parent(parent) {}

                iterator &operator++() {
                    *this = {inner_iterator::operator++(), parent};
                    return *this;
                }
                iterator operator++(int) {
                    iterator tmp = *this;
                    inner_iterator::operator++(0);
                    return {tmp, parent};
                }
                iterator &operator--() {
                    *this = {inner_iterator::operator--(), parent};
                    return *this;
                }
                iterator operator--(int) {
                    iterator tmp = *this;
                    inner_iterator::operator--(0);
                    return tmp;
                }
                value_type operator*() {
                    value_type ref(inner_iterator::operator*());
                    ref.value_will_change([this](inner_value_type v) { if(parent) parent->notify_will_change(); });
                    ref.value_did_change([this](inner_value_type v) { if(parent) parent->notify_did_change(); });
                    return ref;
                }

                const value_type operator*() const {
                    value_type ref(inner_iterator::operator*());
                    ref.value_will_change([this](inner_value_type v) { if(parent) parent->notify_will_change(); });
                    ref.value_did_change([this](inner_value_type v) { if(parent) parent->notify_did_change(); });
                    return ref;
                }

                iterator operator+(size_type n) const { return {inner_iterator::operator+(n), parent}; }
                iterator operator+=(size_type n) { return *this = *this + n; }
                iterator operator-(size_type n) const { return {inner_iterator::operator-(n), parent}; }
                iterator operator-=(size_type n) { return *this = *this - n; }
            private:
                string_notifier *parent;
            };
            using const_iterator = const iterator;

            iterator begin() noexcept { return {type::begin(), this}; }
            iterator end() noexcept { return {type::end(), this}; }
            const_iterator begin() const noexcept { return {type::begin(), this}; }
            const_iterator end() const noexcept { return {type::end(), this}; }
            const_iterator cbegin() const noexcept { return {type::cbegin(), this}; }
            const_iterator cend() const noexcept { return {type::cend(), this}; }

            using reverse_iterator = std::reverse_iterator<iterator>;
            using const_reverse_iterator = std::reverse_iterator<const_iterator>;
            reverse_iterator rbegin() noexcept { return reverse_iterator({type::end(), this}); }
            reverse_iterator rend() noexcept { return reverset_iterator({type::begin(), this}); }
            const_reverse_iterator rbegin() const noexcept { return const_reverset_iterator({type::cend(), this}); }
            const_reverse_iterator rend() const noexcept { return const_reverset_iterator({type::cbegin(), this}); }
            const_reverse_iterator crbegin() const noexcept { return const_reverset_iterator({type::cend(), this}); }
            const_reverse_iterator crend() const noexcept { return const_reverset_iterator({type::cbegin(), this}); }

#define def_overload(meth)\
            template <typename ... arguments>\
            string_notifier & meth(arguments && ... args) {\
                will_change(*this);\
                type::meth(std::forward<arguments>(args) ...);\
                did_change(*this);\
                return *this;\
            }

#define def_void_overload(meth)\
            template <typename ... arguments>\
            void meth(arguments && ... args) {\
                will_change(*this);\
                type::meth(std::forward<arguments>(args) ...);\
                did_change(*this);\
            }

            def_void_overload(resize);

            void reserve(size_type res_arg = 0) {
                will_change(*this);
                type::reserve(res_arg);
                did_change(*this);
            }

            def_void_overload(shrink_to_fit);

            void clear() noexcept {
                will_change(*this);
                type::clear();
                did_change(*this);
            }

            def_overload(operator+=);
            string_notifier &append(const type& str,
                                    size_type pos,
                                    size_type n = npos) {
                will_change(*this);
                type::append(str, pos, n);
                did_change(*this);
            }
            def_overload(append);

            def_void_overload(push_back);
            def_void_overload(pop_back);
            def_overload(assign);

            string_notifier& insert(size_type pos1, const type &str) {
                will_change(*this);
                type::insert(pos1, str);
                did_change(*this);
                return *this;
            }
            string_notifier& insert(size_type pos1, const type& str, size_type pos2, size_type n = npos) {
                will_change(*this);
                type::insert(pos1, str, pos2, n);
                did_change(*this);
                return *this;
            }
            string_notifier& insert(size_type pos, const character_type *s, size_type n) {
                will_change(*this);
                type::insert(pos, n);
                did_change(*this);
                return *this;
            }
            string_notifier& insert(size_type pos, const character_type *s) {
                will_change(*this);
                type::insert(pos, s);
                did_change(*this);
                return *this;
            }
            string_notifier& insert(size_type pos, size_type n, character_type c) {
                will_change(*this);
                type::insert(pos, n, c);
                did_change(*this);
                return *this;
            }

            iterator insert(inner_const_iterator p, character_type c) {
                will_change(*this);
                auto it = type::insert(p, c);
                did_change(*this);
                return {it, this};
            }
            iterator insert(inner_const_iterator p, size_type n, character_type c) {
                will_change(*this);
                auto it = type::insert(p, n, c);
                did_change(*this);
                return {it, this};
            }
            template<typename input_iterator>
            iterator insert(inner_const_iterator p, input_iterator first, input_iterator last) {
                will_change(*this);
                auto it = type::insert(p, first, last);
                did_change(*this);
                return {it, this};
            }
            iterator insert(inner_const_iterator p, std::initializer_list<character_type> l) {
                will_change(*this);
                auto it = type::insert(p, l);
                did_change(*this);
                return {it, this};
            }

            string_notifier& erase(size_type pos = 0, size_type n = npos) {
                will_change(*this);
                type::erase(pos, n);
                did_change(*this);
                return *this;
            }
            iterator erase(inner_const_iterator p) {
                will_change(*this);
                auto it = type::erase(p);
                did_change(*this);
                return {it, this};
            }
            iterator erase(inner_const_iterator first, inner_const_iterator last) {
                will_change(*this);
                auto it = type::erase(first, last);
                did_change(*this);
                return {it, this};
            }

            def_overload(replace);

            void swap(type &str) {
                will_change(*this);
                type::swap(str);
                did_change(*this);
            }

#undef def_overload

            inline void notify_will_change() { will_change(*this); }
            inline void notify_did_change() { did_change(*this); }
            void value_will_change(std::function<void(const type &)> callback) { will_change = callback; }
            void value_did_change(std::function<void(const type &)> callback) { did_change = callback; }

        private:
            std::function<void(const type &)> will_change{[](const type &){}};
            std::function<void(const type &)> did_change{[](const type &){}};
        };
    };
};

#endif /* bbb_type_notifier_string_notifier_hpp */
