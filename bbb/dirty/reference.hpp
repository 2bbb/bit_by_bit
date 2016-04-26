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
                using value_type = type;
                value_type default_value;

                quasi_reference()
                    : default_value() { clear(); }

                quasi_reference(value_type &value)
                    : v(new ref(value)), default_value() { }

                quasi_reference(value_type &value, const value_type &default_value)
                    : v(new ref(value)), default_value(default_value) { }

                quasi_reference &operator=(value_type &value) {
                    v = std::make_shared<ref>(value);
                    return *this;
                }

                operator value_type &() { return v->get(); }

                operator const value_type &() const { return v->get(); }

                inline void clear() { *this = default_value; }

            private:
                struct ref {
                    value_type &v;

                    ref(value_type &v) : v(v) { }

                    value_type &get() { return v; }

                    const value_type &get() const { return v; }
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