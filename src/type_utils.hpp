/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * type_utils.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include "constants.hpp"

#include <type_traits>
#include <tuple>

namespace bbb {
	template <typename T>
	using get_type = typename T::type;

	template <bool b, typename T = void>
	using enable_if = get_type<std::enable_if<b, T>>;

	template <typename T>
	constexpr bool is_const() {
		return std::is_const<T>::value;
	}

	template <typename T>
	constexpr bool is_number() {
		return std::is_arithmetic<T>::value;
	}

	template <typename T>
	constexpr bool is_integer() {
		return std::is_integral<T>::value;
	}

	template <typename T>
	constexpr bool is_float() {
		return std::is_floating_point<T>::value;
	}

	template <typename T>
	using remove_const_reference_if_number = get_type<std::conditional<
		is_number<T>(),
		get_type<std::remove_reference<
			get_type<std::remove_const<T>>
		>>,
		T
	>>;

	template <typename T>
	using add_const_reference_if_not_number = get_type<std::conditional<
		!is_number<T>(),
		get_type<std::add_const<
			get_type<std::add_lvalue_reference<T>>
		>>,
		T
	>>;

	namespace function_traits {
		template <typename T>
		struct function_info : public function_info<decltype(&T::operator())> {};

		template <typename class_type, typename ret, typename ... arguments>
		struct function_info<ret(class_type::*)(arguments ...) const> {
			static constexpr std::size_t arity = sizeof...(arguments);
			using result_type = ret;
			using arguments_types_tuple = std::tuple<arguments ...>;
			template <std::size_t index>
			using argument_type = get_type<std::tuple_element<index, arguments_types_tuple>>;
		};

		template <typename class_type, typename ret, typename ... arguments>
		struct function_info<ret(class_type::*)(arguments ...)> {
			static constexpr std::size_t arity = sizeof...(arguments);
			using result_type = ret;
			using arguments_types_tuple = std::tuple<arguments ...>;
			template <std::size_t index>
			using argument_type = get_type<std::tuple_element<index, arguments_types_tuple>>;
		};

		template <typename ret, typename ... arguments>
		struct function_info<ret(*)(arguments ...)> {
			static constexpr std::size_t arity = sizeof...(arguments);
			using result_type = ret;
			using arguments_types_tuple = std::tuple<arguments ...>;
			template <std::size_t index>
			using argument_type = get_type<std::tuple_element<index, arguments_types_tuple>>;
		};

		template<typename T>
		using result_type = typename function_info<T>::result_type;

		template<typename T>
		using arguments_types_tuple = typename function_info<T>::arguments_types_tuple;

		template<typename T, std::size_t index>
		using argument_type = typename function_info<T>::template argument_type<index>;

		template<typename T>
		struct arity {
			static constexpr std::size_t value = function_info<T>::arity;
		};

		template <typename patient>
		struct has_call_operator {
			template <typename inner_patient, decltype(&inner_patient::operator())> struct checker {};
			template <typename inner_patient> static std::true_type  check(checker<inner_patient, &inner_patient::operator()> *);
			template <typename>               static std::false_type check(...);
			using type = decltype(check<patient>(nullptr));
			static constexpr bool value = type::value;
		};

		template <typename patient>
		constexpr bool is_callable(const patient &) {
			return std::is_function<patient>::value || has_call_operator<patient>::value;
		};
	};
	using namespace function_traits;

	namespace sequences {
		template <typename type, type ... ns>
		struct integer_sequence {
			using value_type = type;
			static constexpr std::size_t size() noexcept { return sizeof...(ns); }
		};

		namespace impl {
			template <typename type, type n, type ... ns>
			struct make_integer_sequence {
				using type = std::conditional<
					n == 0,
					integer_sequence<type, 0, ns ...>,
					get_type<make_integer_sequence<type, n - 1, n - 1, ns ...>>
				>;
			};

		};

		template <typename type, type n>
		using make_integer_sequence = get_type<impl::make_integer_sequence<type, n>>;

		template <std::size_t ... ns>
		using index_sequence = integer_sequence<std::size_t, ns ...>;

		template <std::size_t n>
		using make_index_sequence = make_integer_sequence<std::size_t, n>;

		template <typename... types>
		using index_sequence_for = make_index_sequence<sizeof...(types)>;
	};
	using namespace sequences;
};