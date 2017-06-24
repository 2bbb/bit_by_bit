/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/misc/demangled_type.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <typeinfo>
#include <string>

#ifdef __GNUG__
#   include <cstdlib>
#   include <memory>
#   include <cxxabi.h>
#endif

namespace bbb {
    namespace demangled {
        namespace detail {
            namespace {
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
                };
            };

            template <class type>
            inline std::string demangled_type(const type &t) { return detail::demangle(typeid(t).name()); }
        };
    };
    using namespace demangled;
};