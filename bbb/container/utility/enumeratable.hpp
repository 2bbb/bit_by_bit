/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/container/utility/enumeratable.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once
namespace bbb {
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
