/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/container/utility/reversed_range.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

namespace bbb {
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
}
