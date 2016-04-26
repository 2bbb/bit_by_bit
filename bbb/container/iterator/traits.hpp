/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/container/iterator/traits.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <iterator>

#include <bbb/core.hpp>

namespace bbb {
    namespace container {
        namespace iterator {
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
        };
    };
};
