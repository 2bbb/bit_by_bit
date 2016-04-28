/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/dirty/reference.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

namespace bbb {
    namespace dirty {
        namespace reference {
            template<typename type>
            struct quasi_reference {
                using value_t = type;
                value_t default_value;

                quasi_reference()
                    : default_value() { clear(); }

                quasi_reference(value_t &value)
                    : v(new ref(value)), default_value() { }

                quasi_reference(value_t &value, const value_t &default_value)
                    : v(new ref(value)), default_value(default_value) { }

                quasi_reference &operator=(value_t &value) {
                    v = std::make_shared<ref>(value);
                    return *this;
                }

                operator value_t &() { return v->get(); }
                operator const value_t &() const { return v->get(); }
                inline void clear() { *this = default_value; }

            private:
                struct ref {
                    value_t &v;
                    ref(value_t &v) : v(v) { }
                    value_t &get() { return v; }
                    const value_t &get() const { return v; }
                };

                std::shared_ptr <ref> v;
            };

            template<typename type>
            quasi_reference<type> make_quasi_reference() {
                return quasi_reference<type>();
            }

            template<typename type>
            quasi_reference<type> make_quasi_reference(type &value) {
                return quasi_reference<type>(value);
            }

            template<typename type>
            quasi_reference<type> make_quasi_reference(type &value, const type &default_value) {
                return quasi_reference<type>(value, default_value);
            }
        };
        using namespace reference;
    };
};