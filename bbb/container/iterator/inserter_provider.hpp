/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/container/iterator/inserter_provider.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <iterator>

#include <bbb/core.hpp>

#include <bbb/container/iterator/traits.hpp>

namespace bbb {
    namespace container {
        namespace iterator {
            namespace detail {
                template <typename container>
                struct inserter_provider {
                private:
                    container &body;
                public:
                    inserter_provider(container &body) : body(body) {};

                    template <typename ... arguments>
                    auto insert(arguments ... args)
                    -> decltype(body.insert(args ...)) { return body.insert(args ...); }
                    template <typename ... arguments>
                    auto emplace(arguments ... args)
                    -> decltype(body.emplace(args ...)) { return body.emplace(args ...); }
                };

                template <typename container>
                struct inserter_provider_not {
                    inserter_provider_not(container &) {};
                };
            };

            template <typename container>
            using inserter_provider = typename template_conditional<
                iteratable_class_traits<container>::has_insert,
                detail::inserter_provider,
                detail::inserter_provider_not
            >::template type<container>;

            namespace detail {
                template <typename container>
                struct front_inserter_provider {
                    front_inserter_provider(container &body) : body(body) {};

                    inline void push_front(const typename container::value_type &v) { body.push_front(v); }
                    inline void push_front(typename container::value_type &&v) { body.push_front(v); }
                    template <typename ... arguments>
                    void emplace_front(arguments && ... args) { body.emplace_front(args ...); }
                private:
                    container &body;
                };

                template <typename container>
                struct front_inserter_provider_not {
                    front_inserter_provider_not(container &) {};
                };
            };

            template <typename container>
            using front_inserter_provider = typename template_conditional<
                iteratable_class_traits<container>::has_push_front,
                detail::front_inserter_provider,
                detail::front_inserter_provider_not
            >::template type<container>;

            namespace detail {
                template <typename container>
                struct back_inserter_provider {
                    back_inserter_provider(container &body) : body(body) {};

                    inline void push_back(const typename container::value_type &v) { body.push_back(v); }
                    inline void push_back(typename container::value_type &&v) { body.push_back(v); }
                    template <typename ... arguments>
                    void emplace_back(arguments && ... args) { body.emplace_back(args ...); }
                private:
                    container &body;
                };

                template <typename container>
                struct back_inserter_provider_not {
                    back_inserter_provider_not(container &) {};
                };
            };

            template <typename container>
            using back_inserter_provider = typename template_conditional<
                iteratable_class_traits<container>::has_push_back,
                detail::back_inserter_provider,
                detail::back_inserter_provider_not
            >::template type<container>;
        };
    };
};
