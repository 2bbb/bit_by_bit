/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * misc/demangled_type.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <typeinfo>
#include <string>

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>
#endif

namespace bbb {
    namespace detail {
        std::string demangle(const char *name) {
#ifdef __GNUG__
            int status = -4;
            std::unique_ptr<char, void (*)(void *)> res{
                abi::__cxa_demangle(name, NULL, NULL, &status),
                std::free
            };
            return (status == 0) ? res.get() : name;
#else
            return name;
#endif
        }
    };
};

namespace bbb {
    template <class type>
    std::string demangled_type(const T &t) { return detail::demangle(typeid(t).name()); }
};