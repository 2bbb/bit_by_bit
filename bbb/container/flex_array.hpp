/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/container/flex_array.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

namespace bbb {
    template <std::size_t size, std::size_t ... sizes>
    struct multiply {
        static constexpr std::size_t value = size * multiply<sizes ...>::value;
    };

    template <std::size_t size>
    struct multiply<size> {
        static constexpr std::size_t value = size;
    };

    template <typename value_t, std::size_t size_, std::size_t ... sizes>
    struct flex_array {
        using value_type = value_t;
        using inner_flex_array = flex_array<value_type, sizes ...>;
        std::array<inner_flex_array *, size_> arr;

        template <std::size_t ... indecies>
        flex_array(value_type *body, std::size_t offset, index_sequence<indecies ...>)
        : arr({new flex_array<value_t, sizes ...>(body, offset + indecies * multiply<sizes ...>::value) ...}) {}

        flex_array(value_type *body, std::size_t offset = 0)
        : flex_array(body, offset, make_index_sequence<size_>()) {}

        std::size_t size() const { return size_; }
        std::size_t rank() const { return sizeof...(sizes) + 1; }
        flex_array<value_t, sizes ...> &operator[](std::size_t index) { return *(arr[index]); }
        const flex_array<value_t, sizes ...> &operator[](std::size_t index) const { return *(arr[index]); }
    };

    template <typename value_t, std::size_t size_>
    struct flex_array<value_t, size_> {
        using value_type = value_t;
        value_type * const body;
        flex_array(value_type *body, std::size_t offset = 0)
        : body(body + offset) {}

        std::size_t size() const { return size_; }
        std::size_t rank() const { return 1; }
        value_type &operator[](std::size_t index) { return body[index]; }
        const value_type &operator[](std::size_t index) const { return body[index]; }
    };
};