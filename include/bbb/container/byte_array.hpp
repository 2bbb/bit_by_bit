/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/container/byte_array.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <array>

#include <bbb/container/iterator.hpp>

namespace bbb {
    namespace container {
        template <typename T>
        struct byte_array : iterator_delegation<std::array<std::uint8_t, sizeof(T)>> {
            static_assert(std::is_arithmetic<T>::value, "require: arithmetic type");

            using array_type = std::array<std::uint8_t, sizeof(T)>;
            union {
                T t;
                array_type bytes;
            } raw_val;

#pragma mark byte_array : constructor & operator=

            byte_array()
                : iterator_delegation<std::array<std::uint8_t, sizeof(T)>>(raw_val.bytes) {}

            byte_array(T t)
                : byte_array() { raw_val.t = t; }

            byte_array(const array_type &bytes)
                : byte_array() { raw_val.bytes = bytes; }

            byte_array(array_type &&bytes)
                : byte_array() { raw_val.bytes.swap(bytes); }

            byte_array &operator=(T t) { raw_val.t = t; }
            byte_array &operator=(const array_type &bytes)  { raw_val.bytes = bytes; }
            byte_array &operator=(array_type &bytes) { raw_val.bytes.swap(bytes); }
            byte_array &operator=(array_type &&bytes) { raw_val.bytes.swap(bytes); }

#pragma mark byte_array : cast

            operator T&() { return raw_val.t; }
            operator const T&() const { return raw_val.t; }
            operator array_type&() { return raw_val.bytes; }
            operator const array_type&() const { return raw_val.bytes; }

#pragma mark byte_array : array operatros

            std::uint8_t *data() noexcept { return raw_val.bytes.data(); }
            const std::uint8_t *data() const noexcept { return raw_val.bytes.data(); }

            std::uint8_t &operator[](std::size_t index) { return raw_val.bytes[index]; }
            const std::uint8_t &operator[](std::size_t index) const { return raw_val.bytes[index]; }
            std::uint8_t &at(std::size_t index) { return raw_val.bytes.at(index); }
            const std::uint8_t &at(std::size_t index) const { return raw_val.bytes.at(index); }

            std::uint8_t &front() { return raw_val.bytes.front(); }
            std::uint8_t &back() { return raw_val.bytes.back(); }
            const std::uint8_t &front() const { return raw_val.bytes.front(); }
            const std::uint8_t &back() const { return raw_val.bytes.back(); }

            constexpr std::size_t size() const noexcept { return sizeof(T); }
            constexpr std::size_t max_size() const noexcept { return raw_val.bytes.max_size(); }

            void swap(array_type &arr) noexcept { raw_val.bytes.swap(arr); }
        };
    };
};
