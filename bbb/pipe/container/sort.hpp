/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/pipe/container/sort.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <algorithm>

#include <bbb/core.hpp>

namespace bbb {
    namespace pipe {
        namespace command {
            struct sort {
                sort(const bool desc, const bool use_stable = false)
                : desc(desc)
                , use_stable(use_stable)
                {};

                template <typename container_type>
                friend inline auto operator|=(container_type &cont, sort _)
                    -> type_enable_if_t<
                        is_container<container_type>,
                        container_type &
                    >
                {
                    using std::begin;
                    using std::end;
                    if(_.desc) {
                        std::sort(begin(cont), end(cont),
                                  std::greater<typename container_type::value_type>());
                    } else {
                        std::sort(begin(cont), end(cont),
                                  std::less<typename container_type::value_type>());
                    }
                    return cont;
                }

                template <typename container_type>
                friend inline auto operator|(container_type cont, sort _)
                    -> type_enable_if_t<
                        is_container<container_type>,
                        container_type
                    >
                { return std::move(cont |= _); }

            private:
                const bool desc;
                const bool use_stable;
            };

            template <typename callback_type>
            struct callback_sort {
                callback_sort(callback_type callback, const bool use_stable = false)
                : callback(callback)
                , use_stable(use_stable)
                {};

                template <typename container_type>
                friend inline auto operator|=(container_type &cont, callback_sort _)
                    -> type_enable_if_t<
                        conjunction<
                            is_container<container_type>,
                            is_same<
                                typename function_traits<callback_type>::result_type,
                                bool
                            >,
                            bool_constant<function_traits<callback_type>::arity == 2>
                        >,
                        container_type &
                    >
                {
                    using std::begin;
                    using std::end;
                    if(_.use_stable) {
                        std::stable_sort(begin(cont), end(cont), _.callback);
                    } else {
                        std::sort(begin(cont), end(cont), _.callback);
                    }
                    return cont;
                }

                template <typename container_type>
                friend inline auto operator|=(container_type &cont, callback_sort _)
                    -> type_enable_if_t<
                        conjunction<
                            is_container<container_type>,
                            negation<is_same<
                                typename function_traits<callback_type>::result_type,
                                bool
                            >>,
                            bool_constant<function_traits<callback_type>::arity == 1>
                        >,
                        container_type &
                    >
                {
                    using type = typename container_type::value_type;
                    using std::begin;
                    using std::end;
                    if(_.use_stable) {
                        std::stable_sort(
                            begin(cont),
                            end(cont),
                            [_](const type &a, const type &b) {
                                return _.callback(a) < _.callback(b);
                            }
                        );
                    } else {
                        std::sort(
                            begin(cont),
                            end(cont),
                            [_](const type &a, const type &b) {
                                return _.callback(a) < _.callback(b);
                            }
                        );
                    }
                    return cont;
                }

                template <typename container_type>
                friend inline auto operator|(container_type cont, callback_sort _)
                    -> type_enable_if_t<
                        is_container<container_type>,
                        container_type
                    >
                { return std::move(cont |= _); }

            private:
                callback_type callback;
                const bool use_stable;
            };
        };

        static inline command::sort sort(const bool desc = false, const bool use_stable = false)
        { return {desc, use_stable}; }
        static inline command::sort sort_asc(const bool use_stable = false)
        { return {true, use_stable}; }
        static inline command::sort sort_desc(const bool use_stable = false)
        { return {false, use_stable}; }

        template <typename callback_type>
        static inline auto sort(callback_type callback,  const bool use_stable = false)
        -> command::callback_sort<callback_type> { return {callback, use_stable}; }

        static inline command::sort stable_sort(const bool desc = false) { return {desc, true}; }
        static inline command::sort stable_sort_asc() { return {true, true}; }
        static inline command::sort stable_sort_desc() { return {false, true}; }

        template <typename callback_type>
        static inline auto stable_sort(callback_type callback)
        -> command::callback_sort<callback_type> { return {callback, true}; }
    };
};