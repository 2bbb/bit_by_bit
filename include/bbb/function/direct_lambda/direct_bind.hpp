/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/direct_lambda/binary_function.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <tuple>

#include <bbb/core.hpp>
#include <bbb/tmp.hpp>
#include <bbb/function/direct_lambda/constants.hpp>
#include <bbb/function/direct_lambda/utility.hpp>
#include <bbb/function/direct_lambda/base_class.hpp>
#include <bbb/function/direct_lambda/direct_function.hpp>
#include <bbb/function/direct_lambda/value_holder.hpp>
#include <bbb/function/direct_lambda/placeholder.hpp>
#include <bbb/function/direct_lambda/type_traits.hpp>

namespace bbb {
    namespace function {
        namespace direct_lambda {
            template <typename function_type, typename ... binded_arguments>
            struct direct_function<op_type::binded_function, function_type, binded_arguments ...> {
                std::tuple<function_type, wrap_type_t<binded_arguments> ...> holder;

                using parent_direct_function = direct_function<
                    op_type::binded_function,
                    function_type,
                    wrap_type_t<binded_arguments> ...
                >;
                template <typename ... arguments>
                auto operator()(arguments && ... args) const
                    -> direct_function<
                        op_type::binded_function_apply,
                        function_type,
                        wrap_type_t<binded_arguments> ...,
                        wrap_type_t<arguments> ...
                    >
                {
                    return {
                        std::tuple_cat(
                            holder,
                            std::tuple<wrap_type_t<arguments> ...>(std::forward<arguments>(args) ...)
                        )
                    };
                }
            };

            template <typename function_type, typename ... binded_arguments>
            struct eval<op_type::binded_function, function_type, binded_arguments ...> {
                template <typename ... arguments>
                constexpr function_type evaluate(const std::tuple<function_type, binded_arguments ...> &holder,
                                                 arguments && ... args) const
                {
                    return std::get<0>(holder)(std::forward<arguments>(args) ...);
                }
            };

            template <typename function_type, typename ... binded_arguments_type>
            struct eval<op_type::binded_function_apply, function_type, binded_arguments_type ...> {
                template <typename ... arguments, std::size_t ... indices>
                constexpr auto evaluate_impl(index_sequence<indices ...>,
                                             const std::tuple<function_type, binded_arguments_type ...> &holder,
                                             arguments && ... args) const
                    -> get_type<detect_result_type<
                        function_type,
                        decltype(std::declval<type_at_t<indices, binded_arguments_type ...>>().operator()(
                            std::forward<arguments>(args) ...
                        )) ...
                    >>
                {
                    return (std::get<0>(holder))(
                        std::get<indices + 1>(holder)(std::forward<arguments>(args) ...) ...
                    );
                }

                template <typename ... arguments>
                constexpr auto evaluate(const std::tuple<function_type, binded_arguments_type ...> &holder,
                                        arguments && ... args) const
                    -> decltype(evaluate_impl(
                        make_index_sequence<arity<function_type>::value>(),
                        holder,
                        std::forward<arguments>(args) ...
                    ))
                {
                    return evaluate_impl(
                        make_index_sequence<arity<function_type>::value>(),
                        holder,
                        std::forward<arguments>(args) ...
                    );
                }
            };

            namespace detail {
                template <typename function_type, typename ... arguments, std::size_t index, std::size_t ... indices>
                auto bind_impl(index_sequence<index, indices ...>, function_type f, arguments && ... args)
                    -> direct_function<
                        op_type::binded_function_apply,
                        function_type,
                        wrap_type_t<arguments> ...,
                        placeholder<1 + index>,
                        placeholder<1 + indices> ...
                    >
                {
                    return {
                        std::tuple<
                            function_type,
                            wrap_type_t<arguments> ...,
                            placeholder<1 + index>,
                            placeholder<1 + indices> ...
                        >(
                            f,
                            wrap_type_t<arguments>(std::forward<arguments>(args)) ...,
                            placeholder<1 + index>(),
                            placeholder<1 + indices>() ...
                        )
                    };
                };

                template <typename function_type, typename ... arguments>
                auto bind_impl(index_sequence<>, function_type f, arguments && ... args)
                    -> direct_function<
                        op_type::binded_function_apply,
                        function_type,
                        wrap_type_t<arguments> ...
                    >
                {
                    return {
                        std::tuple<function_type, wrap_type_t<arguments> ...>(
                            f,
                            wrap_type_t<arguments>(std::forward<arguments>(args)) ...
                        )
                    };
                };
            };

            template <typename function_type, typename ... arguments>
            auto bind(function_type f, arguments && ... args)
                -> decltype(detail::bind_impl(
                    make_index_sequence<arity<function_type>::value - sizeof...(args)>(),
                    f,
                    std::forward<arguments>(args) ...
                ))
            {
                return detail::bind_impl(
                    make_index_sequence<arity<function_type>::value - sizeof...(args)>(),
                    f,
                    std::forward<arguments>(args) ...
                );
            };
        };
        using direct_lambda::bind;
    };
};