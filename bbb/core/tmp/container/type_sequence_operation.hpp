/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/type_sequence_operation.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/tmp/traits.hpp>
#include <bbb/core/tmp/container/type_sequence.hpp>

namespace bbb {
    namespace type_sequence_operations {
        template <typename t, typename sequence>
        struct push_front;

        template <typename t, typename sequence>
        using push_front_t = get_type<push_front<t, sequence>>;

        template <typename t, typename ... types>
        struct push_front<t, type_sequence<types ...>> {
            using type = type_sequence<t, types ...>;
        };

        template <typename t, typename sequence>
        struct push_back;

        template <typename t, typename sequence>
        using push_back_t = get_type<push_back<t, sequence>>;

        template <typename t, typename ... types>
        struct push_back<t, type_sequence<types ...>> {
            using type = type_sequence<types ..., t>;
        };

#if BBB_EXEC_UNIT_TEST
        namespace push_test {
            using test1 = unit_test::assert<
                push_front_t<int, type_sequence<float, char>>,
                type_sequence<int, float, char>
            >;
            using test2 = unit_test::assert<
                push_back_t<char, type_sequence<int, float>>,
                type_sequence<int, float, char>
            >;
            using test3 = unit_test::assert<
                push_front_t<int, type_sequence<float, char>>,
                push_back_t<char, type_sequence<int, float>>
            >;
        };
#endif

        template <typename s, typename t>
        struct concat_sequence;

        template <typename s, typename t>
        using concat_sequence_t = get_type<concat_sequence<s, t>>;

        template <typename ... ss, typename ... ts>
        struct concat_sequence<type_sequence<ss ...>, type_sequence<ts ...>> {
            using type = type_sequence<ss ..., ts ...>;
        };

        namespace detail {
            template <typename sequence, typename ... types>
            struct slice;

            template <std::size_t ... indices, typename ... types>
            struct slice<index_sequence<indices ...>, types ...> {
                using type = type_sequence<type_at<indices, types ...> ...>;
            };
        };

        template <std::size_t from, std::size_t to, typename ... types>
        using slice = detail::slice<index_range<from, to>, types ...>;

        template <std::size_t from, std::size_t to, typename ... types>
        using slice_t = get_type<slice<from, to, types ...>>;

#if BBB_EXEC_UNIT_TEST
        namespace slice_test {
            using test1 = unit_test::assert<
                slice_t<0, 1, int, int, char>,
                type_sequence<int, int>
            >;
            using test2 = unit_test::assert<
                slice_t<1, 2, int, int, char>,
                type_sequence<int, char>
            >;
        }
#endif

        template <std::size_t from, std::size_t to, typename sequence>
        struct slice_type_sequence;

        template <std::size_t from, std::size_t to, typename ... types>
        struct slice_type_sequence<from, to, type_sequence<types ...>> {
            using type = slice_t<from, to, types ...>;
        };

        template <std::size_t from, std::size_t to, typename sequence>
        using slice_type_sequence_t = get_type<slice_type_sequence<from, to, sequence>>;

#if BBB_EXEC_UNIT_TEST
        namespace slice_type_sequence_test {
            using test1 = unit_test::assert<
                slice_type_sequence_t<0, 1, type_sequence<int, int, char>>,
                type_sequence<int, int>
            >;
            using test2 = unit_test::assert<
                slice_type_sequence_t<1, 2, type_sequence<int, int, char>>,
                type_sequence<int, char>
            >;
        };
#endif

        template <typename t, typename sequence>
        struct remove;

        template <typename t, typename sequence>
        using remove_t = get_type<remove<t, sequence>>;

        template <typename t, typename u, typename ... types>
        struct remove<t, type_sequence<u, types ...>> {
            using type = conditional_t<
                is_same<t, u>(),
                type_sequence<types ...>,
                push_front_t<u, remove_t<t, type_sequence<types ...>>>
            >;
        };

        template <typename t>
        struct remove<t, type_sequence<>> {
            using type = type_sequence<>;
        };

#if BBB_EXEC_UNIT_TEST
        namespace remove_test {
            using test1 = unit_test::assert<
                remove_t<int, type_sequence<int, int, char>>,
                type_sequence<int, char>
            >;
            using test2 = unit_test::assert<
                remove_t<char, type_sequence<int, int, char>>,
                type_sequence<int, int>
            >;
            using test3 = unit_test::assert<
                remove_t<char, type_sequence<float, int, char, double>>,
                type_sequence<float, int, double>
            >;
            using test3 = unit_test::assert<
                remove_t<char, type_sequence<float, int, double>>,
                type_sequence<float, int, double>
            >;
        };
#endif

        template <typename t, typename sequence>
        struct remove_all;

        template <typename t, typename sequence>
        using remove_all_t = get_type<remove_all<t, sequence>>;

        template <typename t, typename u, typename ... types>
        struct remove_all<t, type_sequence<u, types ...>> {
            using type = conditional_t<
                is_same<t, u>(),
                remove_all_t<t, type_sequence<types ...>>,
                push_front_t<u, remove_all_t<t, type_sequence<types ...>>>
            >;
        };

        template <typename t>
        struct remove_all<t, type_sequence<>> {
            using type = type_sequence<>;
        };

#if BBB_EXEC_UNIT_TEST
        namespace remove_all_test {
            using test1 = unit_test::assert<
                remove_all_t<int, type_sequence<int, int, char>>,
                type_sequence<char>
            >;
            using test2 = unit_test::assert<
                remove_all_t<char, type_sequence<int, int, char>>,
                type_sequence<int, int>
            >;
            using test3 = unit_test::assert<
                remove_all_t<char, type_sequence<float, int, char, double>>,
                type_sequence<float, int, double>
            >;
        };
#endif

        template <typename s, typename t>
        struct difference_sequence;

        template <typename s, typename t>
        using difference_sequence_t = get_type<difference_sequence<s, t>>;

        template <typename s, typename t, typename ... ts>
        struct difference_sequence<s, type_sequence<t, ts ...>> {
            using type = difference_sequence_t<remove_t<t, s>, type_sequence<ts ...>>;
        };

        template <typename s>
        struct difference_sequence<s, type_sequence<>> {
            using type = s;
        };

#if BBB_EXEC_UNIT_TEST
        namespace difference_sequence_test {
            using test1 = unit_test::assert<
                difference_sequence_t<type_sequence<int, int, char>, type_sequence<int>>,
                type_sequence<int, char>
            >;
        };
#endif


        namespace detail {
            template <typename holder, typename ... types>
            struct make_unique;

            template <typename ... holded_types, typename first, typename ... types>
            struct make_unique<type_sequence<holded_types ...>, first, types ...> {
                template <typename rhs>
                using eq = std::is_same<first, rhs>;

                using type = get_type<conditional_t<
                    any_t<eq, holded_types ...>::value,
                    make_unique<type_sequence<holded_types ...>, types ...>,
                    make_unique<type_sequence<holded_types ..., first>, types ...>
                >>;
            };
            template <typename ... holded_types>
            struct make_unique<type_sequence<holded_types ...>> {
                using type = type_sequence<holded_types ...>;
            };
        };

        template <typename ... types>
        using make_unique = detail::make_unique<type_sequence<>, types ...>;
        template <typename ... types>
        using make_unique_t = get_type<make_unique<types ...>>;

#if BBB_EXEC_UNIT_TEST
        namespace make_unique_test {
            using test1 = unit_test::assert<
                make_unique_t<int, int>,
                type_sequence<int>
            >;
            using test2 = unit_test::assert<
                make_unique_t<int, char, int>,
                type_sequence<int, char>
            >;
        }
#endif

        template <typename sequence>
        struct make_sequence_unique;

        template <typename ... types>
        struct make_sequence_unique<type_sequence<types ...>> {
            using type = make_unique_t<types ...>;
        };

        template <typename sequence>
        using make_sequence_unique_t = get_type<make_sequence_unique<sequence>>;

        template <template <typename> class function, typename ... types>
        struct map {
            using type = type_sequence<function<types> ...>;
        };

        template <template <typename> class function, typename ... types>
        using map_t = get_type<map<function, types ...>>;

        template <template <typename> class function, typename sequence>
        struct map_sequence;

        template <template <typename> class function, typename sequence>
        using map_sequence_t = get_type<map_sequence<function, sequence>>;

        template <template <typename> class function, typename ... types>
        struct map_sequence<function, type_sequence<types ...>> {
            using type = map_t<function, types ...>;
        };

#if BBB_EXEC_UNIT_TEST
        namespace map_test {
            template <typename type> using and_true = and_type<std::true_type, type>;
            using test1 = unit_test::assert<
                map_t<and_true, std::true_type, std::false_type>,
                type_sequence<std::true_type, std::false_type>
            >;

            template <typename type> using and_false = and_type<std::false_type, type>;
            using test2 = unit_test::assert<
                map_t<and_false, std::true_type, std::false_type>,
                type_sequence<std::false_type, std::false_type>
            >;

            template <typename type> using or_true = or_type<std::true_type, type>;
            using test3 = unit_test::assert<
                map_t<or_true, std::true_type, std::false_type>,
                type_sequence<std::true_type, std::true_type>
            >;
        };
#endif

        template <template <typename, typename> class function, typename initial, typename ... types>
        struct reduce;

        template <template <typename, typename> class function, typename initial, typename ... types>
        using reduce_t = get_type<reduce<function, initial, types ...>>;

        template <template <typename, typename> class function, typename t, typename s, typename ... types>
        struct reduce<function, t, s, types ...> {
            using type = reduce_t<function, function<t, s>, types ...>;
        };

        template <template <typename, typename> class function, typename t>
        struct reduce<function, t> {
            using type = t;
        };

        template <template <typename, typename> class function, typename sequence>
        struct reduce_sequence;

        template <template <typename, typename> class function, typename sequence>
        using reduce_sequence_t = get_type<reduce_sequence<function, sequence>>;

        template <template <typename, typename> class function, typename t, typename ... types>
        struct reduce_sequence<function, type_sequence<t, types ...>> {
            using type = reduce_t<function, t, types ...>;
        };

#if BBB_EXEC_UNIT_TEST
        namespace reduce_test {
            template <typename seq, typename type>
            using f = push_back_t<type, seq>;
            using test1 = unit_test::assert<
                reduce_t<f, type_sequence<>, int, char, float>,
                type_sequence<int, char, float>
            >;
            using test2 = unit_test::assert<
                reduce_t<or_type, std::true_type, std::false_type, std::false_type>,
                std::true_type
            >;
            using test3 = unit_test::assert<
                reduce_t<or_type, std::false_type, std::false_type, std::false_type>,
                std::false_type
            >;
            using test4 = unit_test::assert<
                reduce_t<and_type, std::true_type, std::false_type, std::false_type>,
                std::false_type
            >;
            using test5 = unit_test::assert<
                reduce_t<and_type, std::true_type, std::true_type, std::true_type>,
                std::true_type
            >;
        };
#endif

        template <typename t, typename u>
        struct make_direct_product;

        template <typename t, typename u>
        using make_direct_product_t = get_type<make_direct_product<t, u>>;

        template <typename ... ts, typename ... us>
        struct make_direct_product<type_sequence<ts ...>, type_sequence<us ...>> {
            template <typename t>
            using make_pair = type_sequence<type_sequence<t, us> ...>;

            using type = reduce_sequence_t<concat_sequence_t, map_t<make_pair, ts ...>>;
        };

#if BBB_EXEC_UNIT_TEST
        namespace make_direct_product_test {
            template <typename ... types>
            using seq = type_sequence<types ...>;
            using test1 = unit_test::assert<
                make_direct_product_t<seq<int, char>, seq<float, double>>,
                seq<seq<int, float>, seq<int, double>, seq<char, float>, seq<char, double>>
            >;

            using p = seq<int, int, int, int>;
            using q = seq<char, char, char, char>;
            static_assert(make_direct_product_t<p, q>::size == p::size * q::size, "");
            static_assert(make_sequence_unique_t<make_direct_product_t<p, q>>::size == make_sequence_unique_t<p>::size * make_sequence_unique_t<q>::size, "");
        };
#endif
    };

    using namespace type_sequence_operations;
};
