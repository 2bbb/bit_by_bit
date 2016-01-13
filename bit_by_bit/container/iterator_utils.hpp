/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * iterator_utils.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include "../core/constants.hpp"
#include "../core/type_utils.hpp"

#include <iterator>

namespace bbb {
#pragma mark iterator_utils

    namespace iterator_utils {
        template <typename container>
        struct iteratable_class_traits {
#pragma mark iterator

            struct forward_iterator_check {
                template <typename testee, typename _ = typename testee::iterator> struct tester {};
                template <typename testee> static std::true_type  test(tester<testee> *);
                template <typename>        static std::false_type test(...);
            };
            static constexpr bool has_iterator = decltype(forward_iterator_check::template test<container>(nullptr))::value;

            struct const_forward_iterator_check {
                template <typename testee, typename _ = typename testee::const_iterator> struct tester {};
                template <typename testee> static std::true_type  test(tester<testee> *);
                template <typename>        static std::false_type test(...);
            };
            static constexpr bool has_const_iterator = decltype(const_forward_iterator_check::template test<container>(nullptr))::value;

            struct reverse_iterator_check {
                template <typename testee, typename _ = typename testee::reverse_iterator> struct tester {};
                template <typename testee> static std::true_type  test(tester<testee> *);
                template <typename>        static std::false_type test(...);
            };
            static constexpr bool has_reverse_iterator = decltype(reverse_iterator_check::template test<container>(nullptr))::value;

            struct const_reverse_iterator_check {
                template <typename testee, typename _ = typename testee::const_reverse_iterator> struct tester {};
                template <typename testee> static std::true_type  test(tester<testee> *);
                template <typename>        static std::false_type test(...);
            };
            static constexpr bool has_const_reverse_iterator = decltype(const_reverse_iterator_check::template test<container>(nullptr))::value;

#pragma mark inserter

            template <typename testee, typename testee::iterator (testee::*)(typename testee::const_iterator, const typename testee::value_type &) = &testee::insert> struct insert_tester {};
            template <typename testee> static std::true_type  insert_test(insert_tester<testee> *);
            template <typename>        static std::false_type insert_test(...);
            static constexpr bool has_insert = decltype(insert_test<container>(nullptr))::value;

            template <typename testee, void (testee::*)(const typename testee::value_type &) = &testee::push_front> struct front_insert_tester {};
            template <typename testee> static std::true_type  push_front_test(front_insert_tester<testee> *);
            template <typename>        static std::false_type push_front_test(...);
            static constexpr bool has_push_front = decltype(push_front_test<container>(nullptr))::value;

            template <typename testee, void (testee::*)(const typename testee::value_type &) = &testee::push_back> struct back_insert_tester {};
            template <typename testee> static std::true_type  push_back_test(back_insert_tester<testee> *);
            template <typename>        static std::false_type push_back_test(...);
            static constexpr bool has_push_back = decltype(push_back_test<container>(nullptr))::value;
        };

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

#pragma mark value_type provider

        template <typename container, bool has_iterator = iteratable_class_traits<container>::has_iterator>
        struct value_type_provider {};

        template <typename container>
        struct value_type_provider<container, true> {
            using value_type = typename std::iterator_traits<typename container::iterator>::value_type;
        };

#pragma mark inserter provider

        template <bool condition, template <typename ...> class t, template <typename ...> class f>
        struct template_conditional {
            template <typename ... arguments>
            using type = get_type<std::conditional<condition, t<arguments ...>, f<arguments ...>>>;
        };

        template <typename container>
        struct inserter_provider_impl {
        private:
            container &body;
        public:
            inserter_provider_impl(container &body) : body(body) {};

            template <typename ... arguments>
            auto insert(arguments ... args)
            -> decltype(body.insert(args ...)) { return body.insert(args ...); }
            template <typename ... arguments>
            auto emplace(arguments ... args)
            -> decltype(body.emplace(args ...)) { return body.emplace(args ...); }
        };

        template <typename container>
        struct inserter_provider_not_impl {
            inserter_provider_not_impl(container &) {};
        };

        template <typename container>
        using inserter_provider = typename template_conditional<
            iteratable_class_traits<container>::has_insert,
            inserter_provider_impl,
            inserter_provider_not_impl
        >::template type<container>;

        template <typename container>
        struct front_inserter_provider_impl {
            front_inserter_provider_impl(container &body) : body(body) {};

            inline void push_front(const typename container::value_type &v) { body.push_front(v); }
            inline void push_front(typename container::value_type &&v) { body.push_front(v); }
            template <typename ... arguments>
            void emplace_front(arguments && ... args) { body.emplace_front(args ...); }
        private:
            container &body;
        };

        template <typename container>
        struct front_inserter_provider_not_impl {
            front_inserter_provider_not_impl(container &) {};
        };

        template <typename container>
        using front_inserter_provider = typename template_conditional<
            iteratable_class_traits<container>::has_push_front,
            front_inserter_provider_impl,
            front_inserter_provider_not_impl
        >::template type<container>;

        template <typename container>
        struct back_inserter_provider_impl {
            back_inserter_provider_impl(container &body) : body(body) {};

            inline void push_back(const typename container::value_type &v) { body.push_back(v); }
            inline void push_back(typename container::value_type &&v) { body.push_back(v); }
            template <typename ... arguments>
            void emplace_back(arguments && ... args) { body.emplace_back(args ...); }
        private:
            container &body;
        };

        template <typename container>
        struct back_inserter_provider_not_impl {
            back_inserter_provider_not_impl(container &) {};
        };

        template <typename container>
        using back_inserter_provider = typename template_conditional<
            iteratable_class_traits<container>::has_push_back,
            back_inserter_provider_impl,
            back_inserter_provider_not_impl
        >::template type<container>;

#pragma mark iterator delegation

        template <typename container>
        struct iterator_delegation
        : iterator_providers<container>::forward_iterator_provider
        , iterator_providers<container>::reverse_iterator_provider
        , inserter_provider<container>
        , front_inserter_provider<container>
        , back_inserter_provider<container>
        , value_type_provider<container> {
        protected:
            using delegation = iterator_delegation<container>;
            iterator_delegation(container &body)
            : iterator_providers<container>::forward_iterator_provider(body)
            , iterator_providers<container>::reverse_iterator_provider(body)
            , inserter_provider<container>(body)
            , front_inserter_provider<container>(body)
            , back_inserter_provider<container>(body) {}
        };
    };
    using namespace iterator_utils;
};
