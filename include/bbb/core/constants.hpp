/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/core/constants.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#if __cplusplus < 201103L
#   error all you need is C++11 (or later)
#elif __cplusplus < 201402L
#   define bbb_is_cpp11 true
#   define bbb_is_cpp14 false
#   define bbb_is_cpp17 false
#else
#   define bbb_is_cpp11 true
#   define bbb_is_cpp14 true
#   define bbb_is_cpp17 false
#endif

namespace bbb {
    constexpr bool is_cpp11() { return bbb_is_cpp11; }
    constexpr bool is_cpp14() { return bbb_is_cpp14; }
    constexpr bool is_cpp17() { return bbb_is_cpp17; }
}

#if bbb_is_cpp11
#   define bbb_constexpr_14 
#   define bbb_constexpr_17 
#elif bbb_is_cpp14
#   define bbb_constexpr_14 constepxr 
#   define bbb_constexpr_17 
#elif bbb_is_cpp17
#   define bbb_constexpr_14 constepxr 
#   define bbb_constexpr_17 constexpr 
#endif

#define BBB_EXEC_UNIT_TEST 1

#define BBB_VERSION_MAJOR 0
#define BBB_VERSION_MINOR 0
#define BBB_VERSION_PATCH 1

#define BBB_MAKE_VERSION(MAJOR, MINOR, PATCH) ((MAJOR * 1000UL + MINOR) * 1000UL + PATCH)
#define BBB_VERSION BBB_MAKE_VERSION(BBB_VERSION_MAJOR, BBB_VERSION_MINOR, BBB_VERSION_PATCH)

#define BBB_IS_VERSION_SAME(MAJOR, MINOR, PATCH) (BBB_MAKE_VERSION(MAJOR, MINOR, PATCH) == BBB_VERSION)
#define BBB_IS_VERSION_NEWER_THAN(MAJOR, MINOR, PATCH) (BBB_MAKE_VERSION(MAJOR, MINOR, PATCH) < BBB_VERSION)
#define BBB_IS_VERSION_NEWER_THAN_EQ(MAJOR, MINOR, PATCH) (BBB_IS_VERSION_NEWER_THAN(MAJOR, MINOR, PATCH) || BBB_IS_VERSION_SAME(MAJOR, MINOR, PATCH))
#define BBB_IS_VERSION_OLDER_THAN(MAJOR, MINOR, PATCH) (!BBB_IS_VERSION_NEWER_THAN_EQ(MAJOR, MINOR, PATCH))
#define BBB_IS_VERSION_OLDER_THAN_EQ(MAJOR, MINOR, PATCH) (!BBB_IS_VERSION_NEWER_THAN(MAJOR, MINOR, PATCH))

#include <cstdint>

namespace bbb {
    using version_major_t = std::uint16_t;
    using version_minor_t = std::uint16_t;
    using version_patch_t = std::uint16_t;
    using version_t = std::uint64_t;

    constexpr version_major_t major() { return BBB_VERSION_MAJOR; };
    constexpr version_minor_t minor() { return BBB_VERSION_MINOR; };
    constexpr version_patch_t patch() { return BBB_VERSION_PATCH; };
    constexpr version_t version() { return BBB_VERSION; };
};

#ifndef __has_feature
#   define __has_feature(x) 0
#endif

#ifndef __has_extension
#   define __has_extension __has_feature
#endif

#ifndef __has_cpp_attribute
#   define __has_cpp_attribute(x) 0
#endif

#if __has_cpp_attribute(clang::fallthrough)
#   define BBB_FALLTHROUGH [[clang::fallthrough]]
#else
#   define BBB_FALLTHROUGH
#endif

#ifndef __has_attribute
#   define __has_attribute(x) 0
#endif

#if __has_cpp_attribute(nodiscard)
#   define BBB_NO_DISCARD [[ nodiscard ]]
#else
#   define BBB_NO_DISCARD
#endif
