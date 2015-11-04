#include <vector>
#include <memory>

namespace bbb {
	template <typename T>
	using shared_vector = std::vector<std::shared_ptr<T>>;
	
	template <typename Container>
	class reverse_range {
		Container &container;
	public:
		reverse_range(Container &cont)
		: container(cont){}
		decltype(container.rbegin()) begin() { return container.rbegin(); }
		decltype(container.rend()) end() { return container.rend(); }
	};
	
	template <typename Container>
	reverse_range<Container> make_reverse(Container &container) {
		return reverse_range<Container>(container);
	}
	
	template <typename Container>
	class const_reverse_range {
		const Container &container;
	public:
		const_reverse_range(const Container &cont)
		: container(cont){}
		decltype(container.rbegin()) begin() const { return container.rbegin(); }
		decltype(container.rend()) end() const { return container.rend(); }
	};
	
	template <typename Container>
	reverse_range<Container> make_const_reverse(const Container &container) {
		return const_reverse_range<Container>(container);
	}
}
