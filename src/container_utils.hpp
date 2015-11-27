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
#include "type_utils.hpp"

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

		using array_type = std::array<std::uint8_t, sizeof(T)>;
		union {
			T t;
			array_type bytes;
		} raw_val;

#pragma mark byte_array : constructor & operator=

		byte_array(T t) { raw_val.t = t; }
		byte_array(const array_type &bytes)  { raw_val.bytes = bytes; }
		byte_array(array_type &&bytes) { raw_val.bytes.swap(bytes); }

		byte_array &operator=(T t) { raw_val.t = t; }
		byte_array &operator=(const array_type &bytes)  { raw_val.bytes = bytes; }
		byte_array &operator=(array_type &&bytes) { raw_val.bytes.swap(bytes); }

#pragma mark byte_array : cast

		operator T&() { return raw_val.t; }
		const operator T&() const { return raw_val.t; }
		operator array_type&() { return raw_val.bytes; }
		const operator array_type&() const { return raw_val.bytes; }

#pragma mark byte_array : array operatros

		std::uint8_t *data() noexcept { return raw_val.bytes.data(); }
		const std::uint8_t *data() const noexcept { return raw_val.bytes.data(); }

		std::uint8_t &operator[](std::size_t index) { return raw_val.bytes[index]; }
		const std::uint8_t &operator[](std::size_t index) const { return raw_val.bytes[index]; }
		std::uint8_t &at(std::size_t index) { return raw_val.bytes.at(index); }
		const std::uint8_t &at(std::size_t index) const { return raw_val.bytes.at(index); }

		std::uint8_t &front() { return raw_val.bytes.front(); }
		std::uint8_t &back() { return raw_val.bytes.back(); }
		const std::uint8_t &front() const { return raw_val.bytes.front(); }
		const std::uint8_t &back() const { return raw_val.bytes.back(); }

		constexpr std::size_t size() const noexcept { return sizeof(T); }
		constexpr std::size_t max_size() const noexcept { return raw_val.bytes.max_size(); }

		void swap(array_type &arr) noexcept { raw_val.bytes.swap(arr); }

#pragma mark byte_array : iteator

		using iterator       = typename array_type::iterator;
		using const_iterator = typename array_type::const_iterator;
		using reverse_iterator       = typename array_type::reverse_iterator;
		using const_reverse_iterator = typename array_type::const_reverse_iterator;

		iterator begin() noexcept { return raw_val.bytes.begin(); }
		iterator end() noexcept { return raw_val.bytes.end(); }
		const_iterator begin() const noexcept { return raw_val.bytes.cbegin(); }
		const_iterator end() const noexcept { return raw_val.bytes.cend(); }
		const_iterator cbegin() const noexcept { return raw_val.bytes.cbegin(); }
		const_iterator cend() const noexcept { return raw_val.bytes.cend(); }
		iterator rbegin() noexcept { return raw_val.bytes.begin(); }
		iterator rend() noexcept { return raw_val.bytes.end(); }
		const_iterator rbegin() const noexcept { return raw_val.bytes.cbegin(); }
		const_iterator rend() const noexcept { return raw_val.bytes.cend(); }
		const_iterator crbegin() const noexcept { return raw_val.bytes.cbegin(); }
		const_iterator crend() const noexcept { return raw_val.bytes.cend(); }
	};

#pragma mark range

	class range {
		const long start, last, offset;
	public:
		range(long start, long last, long offset)
		: start(start)
		, last(last)
		, offset(offset) {}

		range(long start, long last)
		: range(start, last, (0 < last - start) ? 1 : -1) {}

		range(long last)
		: range(0, last) {}

		class range_iterator : public std::iterator<std::random_access_iterator_tag, long> {
			long current;
			const range * const body;

			range_iterator(const range * const body, long current)
			: body(body)
			, current(current) {}

			range_iterator()
			: range_iterator(nullptr, 0) {}

			friend range;
		public:
			range_iterator(const range_iterator &it)
			: range_iterator(it.body, it.current) {}

			long operator*() const { return current; }
			long &operator*() { return current; }

			range_iterator &operator++() {
				current += body->offset;
				if(0 < body->offset && body->last < current) current = body->last;
				else if(body->offset < 0 && current < body->last) current = body->last;
				return *this;
			}
			range_iterator operator++(int) {
				range_iterator tmp{*this};
				++(*this);
				return tmp;
			}
			range_iterator &operator+=(long offset) {
				current += offset * body->offset;
				if(0 < body->offset && body->last < current) current = body->last;
				else if(body->offset < 0 && current < body->last) current = body->last;
				return *this;
			}

			range_iterator &operator--() {
				current -= body->offset;
				if(0 < body->offset && current < body->start) current = body->start;
				else if(0 < body->offset && body->start < current) current = body->start;
				return *this;
			}
			range_iterator operator--(int) {
				range_iterator tmp{*this};
				--(*this);
				return tmp;
			}
			range_iterator &operator-=(long offset) {
				current -= offset * body->offset;
				if(0 < body->offset && current < body->start) current = body->start;
				else if(0 < body->offset && body->start < current) current = body->start;
				return *this;
			}

			inline bool operator==(const range_iterator &it) const { return body == it.body && current == it.current; }
			inline bool operator!=(const range_iterator &it) const { return !(*this == it); }
			inline bool operator<(const range_iterator &it) const  { return body == it.body && current < it.current; }
			inline bool operator<=(const range_iterator &it) const { return body == it.body && current <= it.current; }
			inline bool operator>(const range_iterator &it) const  { return body == it.body && current > it.current; }
			inline bool operator>=(const range_iterator &it) const { return body == it.body && current >= it.current; }
		};

		using iterator = range_iterator;
		using const_iterator = const range_iterator;
		iterator begin() { return iterator(this, start); }
		iterator end() { return iterator(this, last); }
		const_iterator begin() const { return iterator(this, start); }
		const_iterator end() const { return iterator(this, last); }
		const_iterator cbegin() const { return iterator(this, start); }
		const_iterator cend() const { return iterator(this, last); }
	};

#pragma mark enumeratable

	namespace enumeratable {
		template <typename Container>
		class enumeratable_iterator;

		template<typename Container>
		class enumeratable_wrapper {
			Container &body;
			friend enumeratable_iterator<Container>;
		public:
			enumeratable_wrapper(Container &body)
			: body(body) {}

			using value_type = decltype(*(std::begin(body)));

			using iterator = enumeratable_iterator<Container>;
			using const_iterator = enumeratable_iterator<const Container>;

			iterator begin() {  return iterator(this, 0); }
			iterator end() { return iterator(this, body.size()); }
			const_iterator begin() const { return const_iterator(this, 0); }
			const_iterator end() const { return const_iterator(this, body.size()); }
			const_iterator cbegin() const { return const_iterator(this, 0); }
			const_iterator cend() const { return const_iterator(this, body.size()); }

			struct wrapped_value {
				std::size_t index;
				value_type &value;

				wrapped_value(std::size_t index, value_type &v)
				: index(index)
				, value(v) {}
			};

			struct const_wrapped_value {
				std::size_t index;
				const value_type &value;

				const_wrapped_value(std::size_t index, const value_type &v)
				: index(index)
				, value(v) {}
			};
		};

		template <typename Container>
		class enumeratable_iterator : public std::iterator<std::forward_iterator_tag, typename enumeratable_wrapper<Container>::wrapped_value> {
			using wrapped_value = get_type<std::conditional<
					std::is_const<Container>::value,
					typename enumeratable_wrapper<Container>::const_wrapped_value,
					typename enumeratable_wrapper<Container>::wrapped_value
			>>;
			using value_iterator = get_type<std::conditional<
					std::is_const<Container>::value,
					typename Container::const_iterator,
					typename Container::iterator
			>>;
			friend enumeratable_wrapper<Container>;

			std::size_t current;
			enumeratable_wrapper<Container> *parent;
			value_iterator it, last;

			enumeratable_iterator()
			: current(0)
			, parent(nullptr) {}

			enumeratable_iterator(enumeratable_wrapper<Container> *parent, std::size_t current)
			: current(current)
			, parent(parent)
			, it(parent->body.begin() + current)
			, last(parent->body.end()) {
				update_value();
			}

			std::unique_ptr<wrapped_value> value;
			inline void update_value() {
				value = std::unique_ptr<wrapped_value>{new wrapped_value(current, *it)};
			}
		public:
			enumeratable_iterator(const enumeratable_iterator &it)
			: enumeratable_iterator(it.parent, it.current) {}

			enumeratable_iterator &operator++() {
				it++, current++;
				update_value();
				return *this;
			}

			enumeratable_iterator operator++(int) {
				enumeratable_iterator tmp(*this);
				++(*this);
				return tmp;
			}

			wrapped_value &operator*() { return *(value.get()); }
			const wrapped_value &operator*() const { return *(value.get()); }
			decltype(it.operator->()) operator->() { return it.operator->(); }
			const decltype(it.operator->()) operator->() const { return it.operator->(); }
			inline bool operator==(const enumeratable_iterator &rhs) const { return it == rhs.it; }
			inline bool operator!=(const enumeratable_iterator &rhs) const { return it != rhs.it; }
		};

		template<typename Container>
		enumeratable_wrapper<Container> enumerate(Container &t) {
			return {t};
		}

		template<typename Container>
		enumeratable_wrapper<const Container> enumerate(const Container &t) {
			return {t};
		}
	};
	using namespace enumeratable;
};

