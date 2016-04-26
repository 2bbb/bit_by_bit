/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * functional_base.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include "../core/constants.hpp"
#include "../core/type_utils.hpp"

#include "./container_utils.hpp"
#include "./iterator_utils.hpp"

namespace bbb {
    template <typename container_type, typename inner_container_t>
    struct functional_base;

    template <typename inner_container_t, template <typename, typename ...> class container_type, typename value_type, typename ... others>
    struct functional_base<container_type<value_type, others ...>, inner_container_t>
    : iterator_delegation<inner_container_t> {
    protected:
        using functional = functional_base;
        functional_base(inner_container_t &body)
            : iterator_delegation<typename container_type<value_type, others ...>::inner_container_t>(body) {};
    public:
        using value_t = value_type;
        using container_t = container_type<value_t, others ...>;
        template <typename other_value_t>
        using other_container_t = container_type<other_value_t, others ...>;

        using delegation = typename iterator_delegation<inner_container_t>::delegation;
        using delegation::begin;
        using delegation::end;
        using delegation::cbegin;
        using delegation::cend;
        using delegation::rbegin;
        using delegation::rend;
        using delegation::crbegin;
        using delegation::crend;

        using arg_value_t = add_const_reference_if_not_number<value_t>;
        virtual std::size_t size() const = 0;

        virtual void push(const value_t &value) = 0;
        virtual void push(value_t &&value) = 0;

#pragma mark filter
        using filter_predicate_t = std::function<bool(arg_value_t value)>;
        using indexed_filter_predicate_t = std::function<bool(arg_value_t value, std::size_t index)>;
        using stoppable_indexed_filter_predicate_t = std::function<bool(arg_value_t value, std::size_t index, bool *stop)>;

        container_t filter(filter_predicate_t predicate) const {
            container_t results;
            for(auto it = cbegin(); it != cend(); ++it) if(predicate(*it)) results.push(*it);
            return results;
        }

        container_t filter(indexed_filter_predicate_t predicate) const {
            container_t results;
            std::size_t i{0};
            for(auto it = cbegin(); it != cend(); ++it, ++i) if(predicate(*it, i)) results.push(*it);
            return results;
        }

        container_t filter(stoppable_indexed_filter_predicate_t predicate) const {
            container_t results;
            bool stop = false;
            std::size_t i{0};
            for(auto it = cbegin(); !stop && it != cend(); ++it, ++i) if(predicate(*it, i, &stop)) results.push(*it);
            return results;
        }

        template<typename lambda>
        auto filter(lambda &f) const
        -> enable_if<has_call_operator<lambda>::value, container_t> {
            filter(static_cast<typename function_info<lambda>::function_type>(f));
        }

#pragma mark each
        using each_callback_t = std::function<void(arg_value_t value)>;
        using indexed_each_callback_t = std::function<void(arg_value_t value, std::size_t index)>;
        using stoppable_indexed_each_callback_t = std::function<void(arg_value_t value, std::size_t index, bool *stop)>;

        void each(each_callback_t f) const {
            std::for_each(begin(), end(), f);
        }

        void each(indexed_each_callback_t f) const {
            std::size_t i{0};
            for(auto it = cbegin(); it != cend(); ++it, ++i) f(*it, i);
        }

        void each(stoppable_indexed_each_callback_t f) const {
            bool stop = false;
            std::size_t i{0};
            for(auto it = cbegin(); !stop && it != cend(); ++it, ++i) f(*it, i, &stop);
        }

        template<typename lambda>
        auto each(lambda &f) const
        -> enable_if<has_call_operator<lambda>::value> {
            each(static_cast<typename function_info<lambda>::function_type>(f));
        }

#pragma mark destructive_each
        using destructive_each_callback_t = std::function<void(value_t &value)>;
        using indexed_destructive_each_callback_t = std::function<void(value_t &value, std::size_t index)>;
        using stoppable_indexed_destructive_each_callback_t = std::function<void(value_t &value, std::size_t index, bool *stop)>;

        void destructive_each(destructive_each_callback_t f) {
            std::for_each(begin(), end(), f);
        }

        void destructive_each(indexed_destructive_each_callback_t f) {
            std::size_t i{0};
            for(auto it = begin(); it != end(); ++it, ++i) f(*it, i);
        }

        void destructive_each(stoppable_indexed_destructive_each_callback_t f) {
            bool stop = false;
            std::size_t i{0};
            for(auto it = begin(); !stop && it != end(); ++it, ++i) f(*it, i, &stop);
        }

        template<typename lambda>
        auto destructive_eacheach(lambda &f) const
        -> enable_if<has_call_operator<lambda>::value> {
            destructive_eacheach(static_cast<typename function_info<lambda>::function_type>(f));
        }

#pragma mark map
        template <typename result_t>
        using map_callback_t = std::function<result_t(arg_value_t)>;
        template <typename result_t>
        using indexed_map_callback_t = std::function<result_t(arg_value_t, std::size_t index)>;
        template <typename result_t>
        using stoppable_indexed_map_callback_t = std::function<result_t(arg_value_t, std::size_t index, bool *stop)>;

        template <typename result_t>
        other_container_t<result_t> map(map_callback_t<result_t> f) const {
            other_container_t<result_t> results(size());
            auto dst = results.begin();
            for(auto it = cbegin(); it != cend(); ++it, ++dst) *dst = std::move(f(*it));
            return results;
        }

        template <typename result_t>
        other_container_t<result_t> map(indexed_map_callback_t<result_t> f) const {
            other_container_t<result_t> results(size());
            auto dst = results.begin();
            std::size_t i = 0;
            for(auto it = cbegin(); it != cend(); ++it, ++dst, ++i) *dst = std::move(f(*it, i));
            return results;
        }

        template <typename result_t>
        other_container_t<result_t> map(stoppable_indexed_map_callback_t<result_t> f) const {
            other_container_t<result_t> results;
            std::size_t i = 0;
            bool stop = false;
            for(auto it = cbegin(); !stop && it != cend(); ++it, ++i) results.push(std::move(f(*it, i, &stop)));
            return results;
        }

        template<typename lambda>
        auto map(lambda f) const
        -> decltype(map(static_cast<typename function_info<lambda>::function_type>(f)))
        {
            return map(static_cast<typename function_info<lambda>::function_type>(f));
        }

#pragma mark reduce (foldl)
        template <typename result_t>
        using reduce_callback_t = std::function<result_t(result_t &&, arg_value_t)>;
        template <typename result_t>
        using indexed_reduce_callback_t = std::function<result_t(result_t &&, arg_value_t, std::size_t index)>;
        template <typename result_t>
        using stoppable_indexed_reduce_callback_t = std::function<result_t(result_t &&, arg_value_t, std::size_t index, bool *stop)>;
        template <typename result_t>
        using fundamental_reduce_callback_t = std::function<result_t(result_t, arg_value_t)>;
        template <typename result_t>
        using fundamental_indexed_reduce_callback_t = std::function<result_t(result_t, arg_value_t, std::size_t index)>;
        template <typename result_t>
        using fundamental_stoppable_indexed_reduce_callback_t = std::function<result_t(result_t, arg_value_t, std::size_t index, bool *stop)>;

        template<typename result_t>
        result_t reduce(reduce_callback_t<result_t> f,
                        result_t &&initial_value = result_t()) const
        {
            result_t result = std::move(initial_value);
            for(auto it = begin(); it != end(); ++it) result = f(std::move(result), *it);
            return result;
        }

        template<typename result_t>
        result_t reduce(fundamental_reduce_callback_t<result_t> f,
                        result_t initial_value = result_t()) const
        {
            result_t result = initial_value;
            for(auto it = begin(); it != end(); ++it) result = f(result, *it);
            return result;
        }

        template<typename result_t>
        result_t reduce(indexed_reduce_callback_t<result_t> f,
                        result_t &&initial_value = result_t()) const
        {
            result_t result = std::move(initial_value);
            std::size_t i{0};
            for(auto it = begin(); it != end(); ++it, ++i) result = f(std::move(result), *it, i);
            return result;
        }

        template<typename result_t>
        result_t reduce(fundamental_indexed_reduce_callback_t<result_t> f,
                        result_t initial_value = result_t()) const
        {
            result_t result = std::move(initial_value);
            std::size_t i{0};
            for(auto it = begin(); it != end(); ++it, ++i) result = f(result, *it, i);
            return result;
        }

        template<typename result_t>
        result_t reduce(stoppable_indexed_reduce_callback_t<result_t> f,
                        result_t &&initial_value = result_t()) const
        {
            result_t result = std::move(initial_value);
            std::size_t i{0};
            bool stop = false;
            for(auto it = begin(); !stop && it != end(); ++it, ++i) result = f(std::move(result), *it, i, &stop);
            return result;
        }

        template<typename result_t>
        result_t reduce(fundamental_stoppable_indexed_reduce_callback_t<result_t> f,
                        result_t initial_value = result_t()) const
        {
            result_t result = std::move(initial_value);
            std::size_t i{0};
            bool stop = false;
            for(auto it = begin(); !stop && it != end(); ++it, ++i) result = f(result, *it, i, &stop);
            return result;
        }

        template<typename lambda, typename result_t = typename function_info<lambda>::result_type>
        result_t reduce(lambda f, result_t &&initial_value = result_t()) const
        {
            return reduce(static_cast<typename function_info<lambda>::function_type>(f), std::move(initial_value));
        }

#pragma mark foldr
        template<typename result_t>
        result_t foldr(reduce_callback_t<result_t> f,
                       result_t &&initial_value = result_t()) const
        {
            result_t result = std::move(initial_value);
            for(auto it = crbegin(); it != crend(); ++it) result = f(std::move(result), *it);
            return result;
        }

        template<typename result_t>
        result_t foldr(fundamental_reduce_callback_t<result_t> f,
                       result_t initial_value = result_t()) const
        {
            result_t result = initial_value;
            for(auto it = crbegin(); it != crend(); ++it) result = f(result, *it);
            return result;
        }

        template<typename result_t>
        result_t foldr(indexed_reduce_callback_t<result_t> f,
                       result_t &&initial_value = result_t()) const
        {
            result_t result = std::move(initial_value);
            std::size_t i{0};
            for(auto it = crbegin(); it != crend(); ++it, ++i) result = f(std::move(result), *it, i);
            return result;
        }

        template<typename result_t>
        result_t foldr(fundamental_indexed_reduce_callback_t<result_t> f,
                       result_t initial_value = result_t()) const
        {
            result_t result = std::move(initial_value);
            std::size_t i{0};
            for(auto it = crbegin(); it != crend(); ++it, ++i) result = f(result, *it, i);
            return result;
        }

        template<typename result_t>
        result_t foldr(stoppable_indexed_reduce_callback_t<result_t> f,
                       result_t &&initial_value = result_t()) const
        {
            result_t result = std::move(initial_value);
            std::size_t i{0};
            bool stop = false;
            for(auto it = crbegin(); !stop && it != crend(); ++it, ++i) result = f(std::move(result), *it, i, &stop);
            return result;
        }

        template<typename result_t>
        result_t foldr(fundamental_stoppable_indexed_reduce_callback_t<result_t> f,
                       result_t initial_value = result_t()) const
        {
            result_t result = std::move(initial_value);
            std::size_t i{0};
            bool stop = false;
            for(auto it = crbegin(); !stop && it != crend(); ++it, ++i) result = f(result, *it, i, &stop);
            return result;
        }

        template<typename result_t, typename lambda>
        result_t foldr(lambda f, result_t &&initial_value = result_t()) const
        {
            return foldr(static_cast<typename function_info<lambda>::function_type>(f), std::move(initial_value));
        }

        template<typename lambda, typename result_t = typename function_info<lambda>::result_type>
        result_t foldr(lambda f, result_t initial_value = result_t()) const
        {
            return foldr(static_cast<typename function_info<lambda>::function_type>(f), std::move(initial_value));
        }
    };
};