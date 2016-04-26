/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/dirty/static_variable_provider.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

namespace bbb {
    namespace dirty {
        struct static_variable_provider {
            template <typename type, std::size_t>
            static type &get_static() {
                static type _{};
                return _;
            }

            template <typename type, std::size_t id>
            static const type &get_static_as_const() {
                return get_static<type, id>();
            }

            template <typename type, std::size_t id>
            static void set_static(const type &value) {
                std::cout << "const reference" << std::endl;
                get_static<type, id>() = value;
            }

            template <typename type, std::size_t id>
            static void set_static(type &&value) {
                std::cout << "move" << std::endl;
                get_static<type, id>() = std::move(value);
            }
        };
    }
}