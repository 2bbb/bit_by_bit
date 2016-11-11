/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/container/reusable_array.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <memory>
#include <array>
#include <iterator>

#include <bbb/core.hpp>

namespace bbb {
	template <typename T, std::size_t s>
	class reusable_array_iterator;
	template <typename T, std::size_t s>
	class reusable_array_reverse_iterator;
	template <typename T, std::size_t s>
	using reusable_array_const_iterator = reusable_array_iterator<const T, s>;
	template <typename T, std::size_t s>
	using reusable_array_const_reverse_iterator = reusable_array_reverse_iterator<const T, s>;

	template <typename T, std::size_t s>
	class reusable_array {
		static_assert(std::is_default_constructible<T>::value, "require: default constructor");
		static_assert(&T::update, "require: `bool T::update()`");
		static_assert(&T::init, "reuiqre: `void T::init()`");

		friend reusable_array_iterator<T, s>;
		friend reusable_array_iterator<const T, s>;
		friend reusable_array_reverse_iterator<T, s>;
		friend reusable_array_reverse_iterator<const T, s>;

		std::array<T, s> impl;
		std::array<T *, s> arr;
		std::size_t cursor;
	public:
		reusable_array() : cursor(0) {
			for(std::size_t i = 0; i < s; i++) arr[i] = &impl[i];
		}
		
		~reusable_array() {}

		constexpr std::size_t size() const { return s; }
		inline std::size_t current_size() const { return cursor; }
		inline bool has_space() const { return current_size() < size(); }
		
		template <typename ... Args>
		bool init(const Args & ... args) {
			if(has_space()) arr[cursor++]->init(args ...);
			return has_space();
		}
		
		void update() {
			if(!cursor) return;
			std::size_t i = cursor;
			T *tmp(nullptr);
			while(i--) {
				if(arr[i]->update()) continue;
				if(i != --cursor) {
					tmp = arr[i];
					arr[i] = arr[cursor];
					arr[cursor] = tmp;
				}
			}
		}
		
		inline T &operator[](std::size_t index) {
			return *arr[index];
		}
		
		inline T *operator+(std::size_t i) {
			return arr[index];
		}

#pragma mark iterator

		using iterator = reusable_array_iterator<T, s>;
		using const_iterator = reusable_array_const_iterator<T, s>;
		using reverse_iterator = reusable_array_reverse_iterator<T, s>;
		using const_reverse_iterator = reusable_array_const_reverse_iterator<T, s>;

		iterator begin() { return iterator(this, 0); }
		iterator end() { return iterator(this, current_size()); }

		const_iterator begin() const { return const_iterator(this, 0); }
		const_iterator end() const { return const_iterator(this, current_size()); }

		const_iterator cbegin() const { return const_iterator(this, 0); }
		const_iterator cend() const { return const_iterator(this, current_size()); }

		reverse_iterator rbegin() { return reverse_iterator(this, 0); }
		reverse_iterator rend() { return reverse_iterator(this, current_size()); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(this, 0); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this, current_size()); }

		const_reverse_iterator crbegin() const { return const_reverse_iterator(this, 0); }
		const_reverse_iterator crend() const { return const_reverse_iterator(this, current_size()); }
	};

#pragma mark iterator implementation

	template <typename T, std::size_t s>
	class reusable_array_iterator : public reusable_array_iterator<const T, s> {
		using value_type = T;
		using parent = reusable_array<T, s>;
		friend parent;

		reusable_array_iterator(const parent *body, int index)
		: reusable_array_iterator<const T, s>(body, index) {}

		reusable_array_iterator()
		: reusable_array_iterator(nullptr, s) {}

		using reusable_array_iterator<const T, s>::index;
		using reusable_array_iterator<const T, s>::body;

	public:
		reusable_array_iterator(const reusable_array_iterator &it)
		: reusable_array_iterator(it.body, it.index) {}

		value_type &operator*() { return *(body->arr[index]); }
		value_type *operator->() { return body->arr[index]; }
	};

	template <typename T, std::size_t s>
	class reusable_array_iterator<const T, s> : public std::iterator<std::random_access_iterator_tag, T> {
		using value_type = const T;
		using parent = reusable_array<T, s>;
		friend parent;

	protected:
		std::size_t index;
		const parent *body;

		reusable_array_iterator(const parent *body, int index)
				: body(body)
				, index(index) {}

		reusable_array_iterator()
				: reusable_array_iterator(nullptr, s) {}

	public:
		reusable_array_iterator(const reusable_array_iterator &it)
				: reusable_array_iterator(it.body, it.index) {}

		value_type &operator*() const { return *(body->arr[index]); }
		value_type *operator->() const { return body->arr[index]; }

		reusable_array_iterator &operator++() {
			index++;
			return *this;
		}

		reusable_array_iterator operator++(int) {
			reusable_array_iterator it(*this);
			index++;
			return it;
		}

		reusable_array_iterator &operator+=(std::size_t offset) {
			index += offset;
			return *this;
		}

		reusable_array_iterator &operator--() {
			index--;
			return *this;
		}

		reusable_array_iterator operator--(int) {
			reusable_array_iterator it(*this);
			index--;
			return it;
		}

		reusable_array_iterator &operator-=(std::size_t offset) {
			index -= offset;
			return *this;
		}

		inline bool operator==(const reusable_array_iterator &it) const {
			return body == it.body && index == it.index;
		}

		inline bool operator!=(const reusable_array_iterator &it) const {
			return !(*this == it);
		}

		inline bool operator<(const reusable_array_iterator &it) const {
			return body == it.body && index < it.index;
		}

		inline bool operator<=(const reusable_array_iterator &it) const {
			return body == it.body && index <= it.index;
		}

		inline bool operator>(const reusable_array_iterator &it) const {
			return body == it.body && index > it.index;
		}

		inline bool operator>=(const reusable_array_iterator &it) const {
			return body == it.body && index >= it.index;
		}
	};

	template <typename T, std::size_t s>
	class reusable_array_reverse_iterator : public reusable_array_const_reverse_iterator<T, s> {
		using value_type = T;
		using parent = reusable_array<T, s>;
		friend parent;

		using reusable_array_reverse_iterator<const T, s>::index;
		using reusable_array_reverse_iterator<const T, s>::body;

		reusable_array_reverse_iterator(const parent *body, int index)
				: reusable_array_reverse_iterator<const T, s>(body, index) {}

		reusable_array_reverse_iterator()
				: reusable_array_reverse_iterator(nullptr, s) {}

	public:
		reusable_array_reverse_iterator(const reusable_array_reverse_iterator &it)
				: reusable_array_reverse_iterator(it.body, it.index) {}

		value_type &operator*() { return *(body->arr[body->current_size() - 1 - index]); }
		value_type *operator->() { return body->arr[body->current_size() - 1 - index]; }
	};

	template <typename T, std::size_t s>
	class reusable_array_reverse_iterator<const T, s> : public std::iterator<std::random_access_iterator_tag, T> {
		using value_type = const T;
		using parent = reusable_array<T, s>;
		friend parent;

	protected:
		std::size_t index;
		const parent *body;

		reusable_array_reverse_iterator(const parent *body, int index)
				: body(body)
				, index(index) {}

		reusable_array_reverse_iterator()
				: reusable_array_reverse_iterator(nullptr, s) {}

	public:
		reusable_array_reverse_iterator(const reusable_array_reverse_iterator &it)
				: reusable_array_reverse_iterator(it.body, it.index) {}

		value_type &operator*() const { return *(body->arr[body->current_size() - 1 - index]); }
		value_type *operator->() const { return body->arr[body->current_size() - 1 - index]; }

		reusable_array_reverse_iterator &operator++() {
			index++;
			return *this;
		}

		reusable_array_reverse_iterator operator++(int) {
			reusable_array_reverse_iterator it(*this);
			index++;
			return it;
		}

		reusable_array_reverse_iterator &operator+=(std::size_t offset) {
			index += offset;
			return *this;
		}

		reusable_array_reverse_iterator &operator--() {
			index--;
			return *this;
		}

		reusable_array_reverse_iterator operator--(int) {
			reusable_array_reverse_iterator it(*this);
			index--;
			return it;
		}

		reusable_array_reverse_iterator &operator-=(std::size_t offset) {
			index -= offset;
			return *this;
		}

		inline bool operator==(const reusable_array_reverse_iterator &it) const {
			return body == it.body && index == it.index;
		}

		inline bool operator!=(const reusable_array_reverse_iterator &it) const {
			return !(*this == it);
		}

		inline bool operator<(const reusable_array_reverse_iterator &it) const {
			return body == it.body && index < it.index;
		}

		inline bool operator<=(const reusable_array_reverse_iterator &it) const {
			return body == it.body && index <= it.index;
		}

		inline bool operator>(const reusable_array_reverse_iterator &it) const {
			return body == it.body && index > it.index;
		}

		inline bool operator>=(const reusable_array_reverse_iterator &it) const {
			return body == it.body && index >= it.index;
		}
	};
}