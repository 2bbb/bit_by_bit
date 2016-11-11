/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/container/utility/range.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

namespace bbb {
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
};
