/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/container/container_utils.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include "../core/constants.hpp"
#include "../core/type_utils.hpp"
#include "iterator_utils.hpp"
#include "container_delegation.hpp"

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
	void for_each(Container &&c, Function f) {
		std::for_each(c.begin(), c.end(), f);
	}

	template <typename T>
	struct byte_array : iterator_delegation<std::array<std::uint8_t, sizeof(T)>> {
		static_assert(std::is_arithmetic<T>::value, "require: arithmetic type");

		using array_type = std::array<std::uint8_t, sizeof(T)>;
		union {
			T t;
			array_type bytes;
		} raw_val;

#pragma mark byte_array : constructor & operator=
        byte_array()
        : iterator_delegation<std::array<std::uint8_t, sizeof(T)>>(raw_val.bytes) {}

		byte_array(T t)
        : byte_array() { raw_val.t = t; }

        byte_array(const array_type &bytes)
        : byte_array() { raw_val.bytes = bytes; }

		byte_array(array_type &&bytes)
        : byte_array() { raw_val.bytes.swap(bytes); }

		byte_array &operator=(T t) { raw_val.t = t; }
		byte_array &operator=(const array_type &bytes)  { raw_val.bytes = bytes; }
		byte_array &operator=(array_type &bytes) { raw_val.bytes.swap(bytes); }
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
		template <typename Container, typename inner_iterator, typename value_type>
		class enumeratable_iterator;

		template <typename Container>
		class enumeratable_wrapper {
		public:
			using container_value_type = typename std::iterator_traits<typename Container::iterator>::value_type;
			using iterator = enumeratable_iterator<Container, typename Container::iterator, container_value_type>;
			using const_iterator = enumeratable_iterator<Container, typename Container::const_iterator, const container_value_type>;

			enumeratable_wrapper() = delete;
			enumeratable_wrapper(Container &body) : body(body) {}

			iterator begin() { return iterator(this, 0); }
			iterator end() { return iterator(this, body.size()); }
			const_iterator begin() const { return const_iterator(this, 0); }
			const_iterator end() const { return const_iterator(this, body.size()); }
			const_iterator cbegin() const { return const_iterator(this, 0); }
			const_iterator cend() const { return const_iterator(this, body.size()); }
		private:
			friend iterator;
			friend const_iterator;
			Container &body;
		};

		template <typename Container>
		class enumeratable_wrapper<const Container> {
		public:
			using container_value_type = typename std::iterator_traits<typename Container::const_iterator>::value_type;
			using const_iterator = enumeratable_iterator<const Container, typename Container::const_iterator, const container_value_type>;

			enumeratable_wrapper() = delete;
			enumeratable_wrapper(const Container &body) : body(body) {}

			const_iterator begin() const { return const_iterator(this, 0); }
			const_iterator end() const { return const_iterator(this, body.size()); }
			const_iterator cbegin() const { return const_iterator(this, 0); }
			const_iterator cend() const { return const_iterator(this, body.size()); }
		private:
			friend const_iterator;
			const Container &body;
		};

		template <typename value_type>
		class enumerating_value  {
			std::size_t index_;
			value_type &value_;
		public:
			enumerating_value(std::size_t index, value_type &value)
			: index_(index)
			, value_(value) {}
			std::size_t index() const { return index_; }
			value_type &value() { return value_; }
			const value_type &value() const { return value_; }
		};

		template <typename value_type>
		class enumerating_value<const value_type>  {
			std::size_t index_;
			const value_type &value_;
		public:
			enumerating_value(std::size_t index, const value_type &value)
			: index_(index)
			, value_(value) {}
			std::size_t index() const { return index_; }
			const value_type &value() const { return value_; }
		};

		template <typename value_type>
		value_type &value(enumerating_value<value_type> &v) {
			return v.value();
		}

		template <typename value_type>
		const value_type &value(const enumerating_value<value_type> &v) {
			return v.value();
		}

		template <typename value_type>
		std::size_t index(const enumerating_value<value_type> &v) {
			return v.index();
		}

		template <typename Container, typename inner_iterator, typename value_type>
		class enumeratable_iterator : public std::iterator<std::forward_iterator_tag, enumerating_value<value_type>> {
		public:
			using wrapped_value = enumerating_value<value_type>;
		private:
			using parent_type = enumeratable_wrapper<Container>;
			const parent_type * const parent;
			std::size_t current;

			inner_iterator it, last;
			std::unique_ptr<wrapped_value> value;
			friend parent_type;

			enumeratable_iterator()
			: current(0)
			, parent(nullptr) {}

			enumeratable_iterator(const parent_type * const parent, std::size_t current)
			: current(current)
			, parent(parent)
			, it(parent->body.begin() + current)
			, last(parent->body.end()) {
				update_value();
			}

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

			enumeratable_iterator &operator+=(std::size_t offset) {
				while(offset--) it++, current++;
				update_value();
				return *this;
			}

			wrapped_value &operator*() { return *(value.get()); }
			const wrapped_value &operator*() const { return *(value.get()); }
			wrapped_value *operator->() { return value.get(); }
			const wrapped_value *operator->() const { return value.get(); }
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

