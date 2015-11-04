 #include <type_traits>

namespace bbb {
	template <typename T>
	using get_type = typename T::type;

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
	struct remove_const_reference_if_number_impl {
		using type = get_type<std::conditional<
			is_number<T>(),
			get_type<std::remove_reference<
				get_type<std::remove_const<T>>
			>>,
			T
		>>;
	};

	template <typename T>
	using remove_const_reference_if_number = get_type<remove_const_reference_if_number_impl<T>>;

	template <typename T>
	struct add_const_reference_if_not_number_impl {
		using type = get_type<std::conditional<
		    !is_number<T>(),
			get_type<std::add_const<
				get_type<std::add_lvalue_reference<T>>
			>>,
			T
		>>;
	};

	template <typename T>
	using add_const_reference_if_not_number = get_type<add_const_reference_if_not_number_impl<T>>;
};