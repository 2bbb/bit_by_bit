#include <memory>
#include <array>
#include <iterator>

namespace bbb {
	template <typename U, size_t s0>
	class reusable_array_iterator;

	template <typename T, size_t s>
	class reusable_array {
		static_assert(&T::update, "require: `bool T::update()`");
		static_assert(&T::init, "reuiqre: `void T::init()`");
		std::array<T *, s> arr;
		size_t cursor;

		friend reusable_array_iterator<T, s>;
	public:
		using iterator = reusable_array_iterator<T, s>;
		iterator begin() {
			return iterator(this, 0);
		}

		iterator end() {
			return iterator(this, current_size() - 1);
		}

		reusable_array() : cursor(0) {
			for(size_t i = 0; i < s; i++) arr[i] = new T();
		}
		
		~reusable_array() {
			for(size_t i = 0; i < s; i++) delete arr[i];
		}

		constexpr size_t size() const { return s; }
		inline size_t current_size() const { return cursor; }
		inline bool has_space() const { return current_size() < size(); }
		
		template <typename ... Args>
		bool init(const Args & ... args) {
			if(has_space()) arr[cursor++]->init(args ...);
			return has_space();
		}
		
		void update() {
			if(!cursor) return;
			size_t i = cursor;
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
		
		inline T &operator[](size_t index) {
			return *arr[index];
		}
		
		inline T *operator+(size_t i) {
			return arr[index];
		}
	};

	template <typename T, size_t s>
	class reusable_array_iterator : public std::iterator<std::random_access_iterator_tag, T> {
		friend reusable_array<T, s>;

		size_t index;
		const reusable_array<T, s> *body;

		reusable_array_iterator(const reusable_array<T, s> *body, int index)
				: body(body)
				, index(index) {}

		reusable_array_iterator()
				: reusable_array_iterator(nullptr, s) {}

	public:
		reusable_array_iterator(const reusable_array_iterator &it)
				: reusable_array_iterator(it.body, it.index) {}

		reusable_array_iterator &operator++() {
			index++;
		}

		reusable_array_iterator operator++(int) {
			index++;
		}

		T &operator*() { return *(*body)[index]; }
		const T &operator*() const { return *(*body)[index]; }

		T *operator->() { return body->arr[index]; }
		const T *operator->() const { return body->arr[index]; }

		inline bool operator==(const reusable_array_iterator &it) const {
			return body == it->body && index == it.index;
		}

		inline bool operator!=(const reusable_array_iterator &it) const {
			return !(*this == it);
		}
	};

}