/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/function/polymorphic_lambda.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>
#include <bbb/tmp.hpp>

namespace bbb {
    template <typename ... lambdas>
    struct polymorphic_lambda {
        static constexpr std::size_t size = sizeof...(lambdas);
        
        polymorphic_lambda(lambdas && ... fs)
        : fs(std::forward<lambdas>(fs) ...) {
            static_assert(all_different<typename function_traits<lambdas>::arguments_types_tuple ...>::value, "exists same arguments type");
        };
        
        template <typename ... types>
        struct all_different : bool_constant<type_set_t<types ...>::size == size> {};
        
        template <typename lhs, typename rhs>
        struct is_convertible_tuple : std::false_type {};
        
        template <typename l, typename ... lhs, typename r, typename ... rhs>
        struct is_convertible_tuple<std::tuple<l, lhs ...>, std::tuple<r, rhs ...>>
        : type_conditional_t<
            std::is_convertible<l, r>,
            is_convertible_tuple<std::tuple<lhs ...>, std::tuple<rhs ...>>,
            std::false_type
        > {};
        
        template <typename l, typename r>
        struct is_convertible_tuple<std::tuple<l>, std::tuple<r>>
        : bool_constant<std::is_convertible<l, r>::value> {};
        
        template <typename arguments_tuple, typename ... functions>
        struct index_of_same_arguments;

        template <typename arguments_tuple, typename function, typename ... functions>
        struct index_of_same_arguments<arguments_tuple, function, functions ...>
        : std::integral_constant<
            std::size_t,
            std::is_same<
                arguments_tuple,
                typename function_traits<function>::arguments_types_tuple
            >::value ? (size - sizeof...(functions) - 1)
                     : index_of_same_arguments<
                         arguments_tuple,
                         functions ...
                     >::value
        > {};
        
        template <typename arguments_tuple>
        struct index_of_same_arguments<arguments_tuple> {
            static constexpr std::size_t value = size;
        };
        
        template <typename arguments_tuple, typename ... functions>
        struct index_of_convertible_arguments;

        template <typename arguments_tuple, typename function, typename ... functions>
        struct index_of_convertible_arguments<arguments_tuple, function, functions ...>
        : std::integral_constant<
            std::size_t,
            is_convertible_tuple<
                arguments_tuple,
                typename function_traits<function>::arguments_types_tuple
            >::value ? (size - sizeof...(functions) - 1)
                     : index_of_convertible_arguments<
                         arguments_tuple,
                         functions ...
                     >::value
        > {};
        
        template <typename arguments_tuple>
        struct index_of_convertible_arguments<arguments_tuple> {
            static constexpr std::size_t value = size;
        };
        
        template <typename arguments_tuple, typename ... functions>
        struct index_of {
            static constexpr std::size_t index_of_same_arguments_v = index_of_same_arguments<
                arguments_tuple, functions ...
            >::value;
            static constexpr std::size_t index_of_convertible_arguments_v = index_of_convertible_arguments<
                arguments_tuple, functions ...
            >::value;
            static constexpr std::size_t value = index_of_same_arguments_v < size
                                               ? index_of_same_arguments_v 
                                               : index_of_convertible_arguments_v;
        };

        template <typename ... arguments>
        auto operator()(arguments && ... args) const
            -> enable_if_t<
                index_of<std::tuple<arguments ...>, lambdas ...>::value < size,
                typename function_traits<
                    type_at_t<
                        index_of<std::tuple<arguments ...>, lambdas ...>::value,
                        lambdas ...
                    >
                >::result_type
            >
        {
            return std::get<index_of<std::tuple<arguments ...>, lambdas ...>::value>(fs)(std::forward<arguments>(args) ...);
        }
        
    private:
        std::tuple<lambdas ...> fs;
    };
    
    template <typename ... lambdas>
    auto make_polymorphic_lambda(lambdas && ... fs)
        -> polymorphic_lambda<lambdas ...>
    {
        return {std::forward<lambdas>(fs) ...};
    }
};
