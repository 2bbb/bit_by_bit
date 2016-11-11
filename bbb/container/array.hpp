/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * array.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <initializer_list>

#include <bbb/core.hpp>

#include <bbb/container/utility.hpp>
#include <bbb/container/functional_base.hpp>

namespace bbb {
    namespace container {
        template <typename value_type, typename allocator = std::allocator<value_type>>
        struct array : functional_base<array<value_type, allocator>, std::vector<value_type, allocator>>
        {
            using value_t = value_type;
            using arg_value_t = add_const_reference_if_not_number<value_t>;
            using inner_container_t = std::vector<value_type, allocator>;

            using functional = functional_base<array<value_type, allocator>, inner_container_t>;
#pragma mark constructor
            explicit array(std::size_t size,
                           arg_value_t initial_value = value_t(),
                           const allocator &alloc = allocator())
            : body(size, initial_value, alloc)
            , functional(body) {}

            array(const std::vector<value_t> &values)
            : body(values)
            , functional(body) {}
            array(std::vector<value_t> &&values)
            : body(std::move(values))
            , functional(body) {}

            explicit array(std::size_t size,
                           const allocator &alloc)
            : array(size, value_t(), alloc) {}

            array(const array &other)
            : array(other.body) {}
            array(array &&other)
            : array(std::move(other.body)) {}

            array(const std::initializer_list<value_t> &list)
            : body(list)
            , functional(body) {}

            array()
            : array(0) {}
#pragma mark operator=


#pragma mark other operators

            bool operator==(const array &other) const {
                return (size() == other.size()) && this->reduce([&other](bool, arg_value_t value, std::size_t i, bool *stop) {
                    return !(*stop = (value != other[i]));
                }, true);
            }

            bool operator!=(const array &other) const {
                return (size() != other.size()) || this->reduce([&other](bool, arg_value_t value, std::size_t i, bool *stop) {
                    return !(*stop = (value == other[i]));
                }, true);
            }

#pragma mark cast
            operator std::vector<value_t>&() { return body; }
            operator const std::vector<value_t>&() const { return body; }

#pragma mark element operation
            virtual void push(const value_t &value) override {
                body.push_back(value);
            }

            virtual void push(value_t &&value) override {
                body.push_back(std::move(value));
            }

            value_t pop() {
                value_t t = std::move(body.back());
                body.pop_back();
                return t;
            }

            void unshift(value_t &&) = delete;
            value_t shift() = delete;
            void insert(value_type &&value, std::size_t index) = delete;

#pragma mark accessor
            std::size_t size() const override {
                return body.size();
            }

            const arg_value_t &operator[](std::size_t i) const { return body[i]; }
            arg_value_t &operator[](std::size_t i) { return body[i]; }

        private:
            std::vector<value_t> body;
        };
    };
}
