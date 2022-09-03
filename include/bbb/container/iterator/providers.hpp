/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/container/iterator/providers.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <iterator>

#include <bbb/core.hpp>
#include <bbb/container/iterator/traits.hpp>

namespace bbb {
    namespace container {
        namespace iterator {
            template <typename container>
            struct iterator_providers {
                using traits = iteratable_class_traits<container>;

                struct forward_iterator_provider_not_impl {
                protected:
                    forward_iterator_provider_not_impl(container &) {}
                };

                struct mutable_forward_iterator_provider_impl {
                    using iterator = typename container::iterator;
                    iterator begin() { return body.begin(); }
                    iterator end() { return body.end(); }
                protected:
                    mutable_forward_iterator_provider_impl(container &body) : body(body) {};
                private:
                    container &body;
                };

                struct const_forward_iterator_provider_impl {
                    using const_iterator = typename container::const_iterator;
                    const_iterator begin() const { return body.begin(); }
                    const_iterator end() const { return body.end(); }
                    const_iterator cbegin() const { return body.cbegin(); }
                    const_iterator cend() const { return body.cend(); }
                protected:
                    const_forward_iterator_provider_impl(container &body) : body(body) {};
                private:
                    container &body;
                };

                struct forward_iterator_provider_impl
                    : mutable_forward_iterator_provider_impl
                        , const_forward_iterator_provider_impl {
                    using typename mutable_forward_iterator_provider_impl::iterator;
                    using mutable_forward_iterator_provider_impl::begin;
                    using mutable_forward_iterator_provider_impl::end;

                    using typename const_forward_iterator_provider_impl::const_iterator;
                    using const_forward_iterator_provider_impl::begin;
                    using const_forward_iterator_provider_impl::end;
                    using const_forward_iterator_provider_impl::cbegin;
                    using const_forward_iterator_provider_impl::cend;
                protected:
                    forward_iterator_provider_impl(container &body)
                        : mutable_forward_iterator_provider_impl(body)
                        , const_forward_iterator_provider_impl(body) {}
                };

                struct reverse_iterator_provider_not_impl {
                protected:
                    reverse_iterator_provider_not_impl(container &) {}
                };

                struct mutable_reverse_iterator_provider_impl {
                    using reverse_iterator = typename container::reverse_iterator;
                    reverse_iterator rbegin() { return body.rbegin(); }
                    reverse_iterator rend() { return body.rend(); }
                protected:
                    mutable_reverse_iterator_provider_impl(container &body) : body(body) {}
                private:
                    container &body;
                };

                struct const_reverse_iterator_provider_impl {
                    using const_reverse_iterator = typename container::const_reverse_iterator;
                    const_reverse_iterator rbegin() const { return body.rbegin(); }
                    const_reverse_iterator rend() const { return body.rend(); }
                    const_reverse_iterator crbegin() const { return body.crbegin(); }
                    const_reverse_iterator crend() const { return body.crend(); }
                protected:
                    const_reverse_iterator_provider_impl(container &body) : body(body) {}
                private:
                    container &body;
                };

                struct reverse_iterator_provider_impl
                    : mutable_reverse_iterator_provider_impl
                        , const_reverse_iterator_provider_impl {
                    using typename mutable_reverse_iterator_provider_impl::reverse_iterator;
                    using mutable_reverse_iterator_provider_impl::rbegin;
                    using mutable_reverse_iterator_provider_impl::rend;

                    using typename const_reverse_iterator_provider_impl::const_reverse_iterator;
                    using const_reverse_iterator_provider_impl::rbegin;
                    using const_reverse_iterator_provider_impl::rend;
                    using const_reverse_iterator_provider_impl::crbegin;
                    using const_reverse_iterator_provider_impl::crend;
                protected:
                    reverse_iterator_provider_impl(container &body)
                        : mutable_reverse_iterator_provider_impl(body)
                        , const_reverse_iterator_provider_impl(body) {}
                };

                template <bool has, typename impl, typename not_impl>
                using type_if = get_type<std::conditional<has, impl, not_impl>>;

                template <bool has_mutable, bool has_const, typename mutable_impl, typename const_impl, typename impl, typename not_impl>
                using quad_if = type_if<
                    has_mutable,
                    type_if<has_const, impl, mutable_impl>,
                    type_if<has_const, const_impl, not_impl>
                >;

                using forward_iterator_provider = quad_if<
                    traits::has_iterator, traits::has_const_iterator,
                    mutable_forward_iterator_provider_impl, const_forward_iterator_provider_impl,
                    forward_iterator_provider_impl, forward_iterator_provider_not_impl
                >;
                using reverse_iterator_provider = quad_if<
                    traits::has_reverse_iterator, traits::has_const_reverse_iterator,
                    mutable_reverse_iterator_provider_impl, const_reverse_iterator_provider_impl,
                    reverse_iterator_provider_impl, reverse_iterator_provider_not_impl
                >;
            };
        };
    };
};
