/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * container_utils.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include "constants.hpp"

#include <vector>
#include <memory>
#include <algorithm>

namespace bbb {
	template <typename T>
	using shared_vector = std::vector<std::shared_ptr<T>>;

	template <typename Container>
	class const_reversed_range {
	protected:
		using const_reverse_iterator = typename Container::const_reverse_iterator;
		static_assert(static_cast<const_reverse_iterator (Container::*)() const>(&Container::rbegin),
					  "require: `const_reverse_iterator Container::rbegin() const`");
		static_assert(static_cast<const_reverse_iterator (Container::*)() const>(&Container::rend),
					  "require: `const_reverse_iterator Container::rend() const`");

		const Container &container;
	public:
		const_reversed_range(const Container &cont)
		: container(cont) {}

		const_reverse_iterator begin() const { return container.rbegin(); }
		const_reverse_iterator end() const { return container.rend(); }

		const_reverse_iterator cbegin() const { return container.rbegin(); }
		const_reverse_iterator cend() const { return container.rend(); }
	};

	template <typename Container>
	const_reversed_range<Container> make_const_reverse(const Container &container) {
		return const_reversed_range<Container>(container);
	}

	template <typename Container>
	class reversed_range : public const_reversed_range<Container> {
		using reverse_iterator = typename Container::reverse_iterator;
		using const_reverse_iterator = typename const_reversed_range<Container>::const_reverse_iterator;
		static_assert(static_cast<reverse_iterator (Container::*)()>(&Container::rbegin),
					  "require: `reverse_iterator Container::rbegin()`");
		static_assert(static_cast<reverse_iterator (Container::*)()>(&Container::rend),
					  "require: `reverse_iterator Container::rend()`");

		Container &container;
	public:
		reversed_range(Container &cont)
		: const_reversed_range<Container>(cont)
		, container(cont) {}

		reverse_iterator begin() { return container.rbegin(); }
		reverse_iterator end() { return container.rend(); }
	};
	
	template <typename Container>
	reversed_range<Container> make_reverse(Container &container) {
		return reversed_range<Container>(container);
	}

	template <typename Container, typename Function>
	void for_each(Container &c, Function f) {
		std::for_each(c.begin(), c.end(), f);
	}

	template <typename T>
	struct byte_array {
		static_assert(std::is_arithmetic<T>::value, "require: arithmetic type");
		union {
			T t;
			uint8_t bytes[sizeof(T)];
		} raw_val;

		byte_array(T t) {
			raw_val.t = t;
		}

		size_t size() const {
			return sizeof(T);
		}

		byte_array &operator=(T t) {
			raw_val.t = t;
		}

		uint8_t &operator[](size_t index) {
			return raw_val.bytes[index];
		}

		const uint8_t &operator[](size_t index) const {
			return raw_val.bytes[index];
		}
	};
};

