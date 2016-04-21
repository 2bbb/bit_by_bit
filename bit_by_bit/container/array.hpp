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
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include "../core/constants.hpp"
#include "../core/type_utils.hpp"

#include "../container/container_utils.hpp"

namespace bbb {
    template <typename value_type, typename allocator = std::allocator<value_type>>
    struct array {
        using value_t = value_type;

        using arg_value_t = add_const_reference_if_not_number<value_t>;
        using each_callback_t = std::function<void(arg_value_t value)>;
        using indexed_each_callback_t = std::function<void(arg_value_t value, std::size_t index)>;
        using stoppable_indexed_each_callback_t = std::function<void(arg_value_t value, std::size_t index, bool *stop)>;

#pragma mark constructor
        array() {}

        explicit array(std::size_t size,
                       arg_value_t initial_value = value_t(),
                       const allocator &alloc = allocator())
            : body(size, initial_value, alloc) {}

        explicit array(std::size_t size,
                       const allocator &alloc)
            : array(size, value_t(), alloc) {}

        array(const array &other)
            : body(other.body) {}
        array(array &&other)
            : body(std::move(other.body)) {}

        array(const std::vector<value_t> &values)
            : body(values) {}
        array(std::vector<value_t> &&values)
            : body(std::move(values)) {}

#pragma mark operator=


#pragma mark other operators

        bool operator==(const array &other) const {
            return (size() == other.size()) && reduce([&other](bool, arg_value_t value, std::size_t i, bool *stop) {
                return !(*stop = (value != other[i]));
            }, true);
        }

        bool operator!=(const array &other) const {
            return (size() != other.size()) || reduce([&other](bool, arg_value_t value, std::size_t i, bool *stop) {
                return !(*stop = (value == other[i]));
            }, true);
        }

#pragma mark cast
        operator std::vector<value_t>&() { return body; }
        operator const std::vector<value_t>&() const { return body; }

#pragma mark element operation
        void push(const value_t &t) {
            body.push_back(t);
        }
        void push(value_t &&t) {
            body.push_back(std::move(t));
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
        std::size_t size() const {
            return body.size();
        }

        const arg_value_t &operator[](std::size_t i) const { return body[i]; }
        arg_value_t &operator[](std::size_t i) { return body[i]; }

#pragma mark functional
        void each(each_callback_t f) {
            std::for_each(body.begin(), body.end(), f);
        }

        void each(indexed_each_callback_t f) {
            for(std::size_t i = 0; i < size(); i++) f(body[i], i);
        }

        void each(stoppable_indexed_each_callback_t f) {
            bool stop = false;
            for(std::size_t i = 0; !stop && i < size(); i++) f(body[i], i, &stop);
        }

		template<typename lambda>
		auto each(lambda &f)
        -> enable_if<has_call_operator<lambda>::value> {
			each(static_cast<typename bbb::function_info<lambda>::function_type>(f));
		}

        template <typename result_t>
        array<result_t> map(std::function<result_t(arg_value_t value)> f) {
            array<result_t> results(body.size());
            for(std::size_t i = 0; i < body.size(); i++) results[i] = f(body[i]);
            return results;
        }

        template <typename result_t>
        using reduce_callback_t = std::function<result_t(result_t &&, arg_value_t)>;
        template <typename result_t>
        using indexed_reduce_callback_t = std::function<result_t(result_t &&, arg_value_t, std::size_t index)>;
        template <typename result_t>
        using stoppable_indexed_reduce_callback_t = std::function<result_t(result_t &&, arg_value_t, std::size_t index, bool *stop)>;

        template<typename result_t>
        result_t reduce(reduce_callback_t<result_t> f,
                        result_t &&initial_value = result_t()) const
        {
            result_t result = std::move(initial_value);
            for(std::size_t i = 0; i < size(); i++) result = f(std::move(result), body[i]);
            return result;
        }

        template<typename result_t>
        result_t reduce(indexed_reduce_callback_t<result_t> f,
                        result_t &&initial_value = result_t()) const
        {
            result_t result = std::move(initial_value);
            for(std::size_t i = 0; i < size(); i++) result = f(std::move(result), body[i], i);
            return result;
        }

        template<typename result_t>
        result_t reduce(stoppable_indexed_reduce_callback_t<result_t> f,
                        result_t &&initial_value = result_t()) const
        {
            result_t result = std::move(initial_value);
            std::cout << "BBB" << std::endl;
            bool stop = false;
            for(std::size_t i = 0; !stop && (i < size()); i++) result = f(std::move(result), body[i], i, &stop);
            return result;
        }

        template<typename result_t, typename lambda, typename function_type = typename bbb::function_info<lambda>::function_type, typename arg_result_t = add_const_reference_if_not_number<result_t>>
        auto reduce(lambda f, result_t &&initial_value) const
        -> enable_if<has_call_operator<lambda>::value
                     && !is_same<function_type, reduce_callback_t<arg_result_t>>()
                     && !is_same<function_type, indexed_reduce_callback_t<arg_result_t>>()
                     && !is_same<function_type, stoppable_indexed_reduce_callback_t<arg_result_t>>(), result_t>
        {
            std::cout << "AAA" << std::endl;
            return reduce(static_cast<function_type>(f), std::move(initial_value));
        }

        template<typename result_t>
        result_t foldr(std::function<result_t(result_t &&, arg_value_t)> f,
                       result_t &&initial) const
        {
            result_t res;
            return res;
        }

    private:
        std::vector<value_t> body;
    };
}