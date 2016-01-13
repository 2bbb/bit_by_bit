/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * container_delegation.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include "../core/constants.hpp"
#include "../core/type_utils.hpp"
#include "iterator_utils.hpp"

#include <array>
#include <vector>
#include <memory>
#include <algorithm>

namespace bbb {
    namespace container_delegate {
        template <typename container>
        struct container_delegation;

#pragma mark container_delegation array implementation

        namespace impl {
            template <typename>
            struct is_array {
                static constexpr bool value = false;
            };

            template<typename container>
            struct array_delegation_base {
                using value_type      = typename container::value_type;
                using reference       = typename container::reference;
                using const_reference = typename container::const_reference;
                using size_type       = typename container::size_type;
                using difference_type = typename container::difference_type;

                size_type size() const { return body.size(); };
                constexpr size_type max_size() const noexcept { return body.max_size(); };

                value_type *data() noexcept { return body.data(); }
                const value_type *data() const noexcept { return body.data(); }

                reference operator[](std::size_t index) { return body[index]; }
                reference at(std::size_t index) { return body.at(index); }
                reference front() { return body.front(); }
                reference back() { return body.back(); }

            protected:
                container &body;
                array_delegation_base(container &body) : body(body) {}
            };

            template<typename array_t, bool is_constexpressionable>
            struct array_delegation;

            template<typename array_t>
            struct array_delegation<array_t, true> : array_delegation_base<array_t> {
                using array_delegation_base<array_t>::body;
                using container = array_t;

                using value_type      = typename array_delegation_base<array_t>::value_type;
                using reference       = value_type &;
                using const_reference = const value_type &;
                using size_type       = typename array_delegation_base<array_t>::size_type;
                using difference_type = typename array_delegation_base<array_t>::difference_type;

                constexpr bool empty() const noexcept { return body.empty(); };
                constexpr const_reference operator[](std::size_t index) const { return body[index]; }
                constexpr const_reference at(std::size_t index) const { return body.at(index); }
                constexpr const_reference front() const { return body.front(); }
                constexpr const_reference back() const { return body.back(); }
            protected:
                array_delegation(array_t &arr) : array_delegation_base<array_t>(arr) {}
            };

            template<typename array_t>
            struct array_delegation<array_t, false> : array_delegation_base<array_t> {
                using array_delegation_base<array_t>::body;
                using container = array_t;

                using value_type      = typename array_delegation_base<array_t>::value_type;
                using reference       = value_type &;
                using const_reference = const value_type &;
                using size_type       = typename array_delegation_base<array_t>::size_type;
                using difference_type = typename array_delegation_base<array_t>::difference_type;

                constexpr bool empty() const noexcept { return body.size() == 0; };
                const_reference operator[](std::size_t index) const { return body[index]; }
                const_reference at(std::size_t index) const { return body.at(index); }
                const_reference front() const { return body.front(); }
                const_reference back() const { return body.back(); }
            protected:
                array_delegation(array_t &arr) : array_delegation_base<array_t>(arr) {}
            };
        };

        template <typename array_t>
        using array_delegation = impl::array_delegation<array_t, is_cpp14() && impl::is_array<array_t>::value>;

#pragma mark container_delegation array interface

        template <typename value_t, std::size_t size>
        struct container_delegation<std::array<value_t, size>> : array_delegation<std::array<value_t, size>> {
        protected:
            using container = std::array<value_t, size>;

        private:
            using array_delegation<container>::body;

        protected:
            using delegation = container_delegation<container>;
            container_delegation(container &body) : array_delegation<container>(body) {}
        };

#pragma mark container_delegation vector

        template <typename value_t, typename allocator_t>
        struct container_delegation<std::vector<value_t, allocator_t>>
        : iterator_delegation<std::vector<value_t, allocator_t>> {
        protected:
            using container = std::vector<value_t, allocator_t>;

        private:
            container &body;

        public:
            using value_type      = typename container::value_type;
            using reference       = value_type &;
            using const_reference = const value_type &;
            using size_type       = typename container::size_type;
            using difference_type = typename container::difference_type;

            using allocator_type = typename container::allocator_type;
            using pointer = typename container::pointer;
            using const_pointer = typename container::const_pointer;

            size_type size() const { return body.size(); };
            constexpr size_type max_size() const noexcept { return body.max_size(); };

            value_type *data() noexcept { return body.data(); }
            const value_type *data() const noexcept { return body.data(); }

            reference operator[](std::size_t index) { return body[index]; }
            const_reference operator[](std::size_t index) const { return body[index]; }

            reference at(std::size_t index) { return body.at(index); }
            const_reference at(std::size_t index) const { return body.at(index); }

            reference front() { return body.front(); }
            const_reference front() const { return body.front(); }

            reference back() { return body.back(); }
            const_reference back() const { return body.back(); }

            template <class input_iterator>
            void assign(input_iterator first, input_iterator last) { body.assign(first, last); }
            void assign(size_type n, const value_type& v) { body.assign(n, v); }
            void assign(std::initializer_list<value_type> &list) { body.assign(list); }
        protected:
            using delegation = container_delegation<container>;
            container_delegation(container &body)
            : iterator_delegation<std::vector<value_t, allocator_t>>(body)
            , body(body) {}
        };
    };

    using namespace container_delegate;
};