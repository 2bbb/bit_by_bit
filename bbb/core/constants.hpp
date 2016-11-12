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
#else
#   define bbb_is_cpp11 true
#   define bbb_is_cpp14 true
#endif

namespace bbb {
    constexpr bool is_cpp11() { return bbb_is_cpp11; }
    constexpr bool is_cpp14() { return bbb_is_cpp14; }
}

#define BBB_EXEC_UNIT_TEST 1

#define BBB_VERSION_MAJOR 0
#define BBB_VERSION_MINOR 0
#define BBB_VERSION_PATCH 1

#define BBB_MAKE_VERSION(MAJOR, MINOR, PATCH) (((MAJOR * 1000UL + MINOR) * 1000UL + PATCH)
#define BBB_VERSION BBB_MAKE_VERSION(BBB_VERSION_MAJOR, BBB_VERSION_MINOR, BBB_VERSION_PATCH)

#define BBB_IS_VERSION_SAME(MAJOR, MINOR, PATCH) (BBB_MAKE_VERSION(MAJOR, MINOR, PATCH) == BBB_VERSION)
#define BBB_IS_VERSION_NEWER_THAN(MAJOR, MINOR, PATCH) (BBB_MAKE_VERSION(MAJOR, MINOR, PATCH) < BBB_VERSION)
#define BBB_IS_VERSION_NEWER_THAN_EQ(MAJOR, MINOR, PATCH) (BBB_IS_VERSION_NEWER_THAN(MAJOR, MINOR, PATCH) || BBB_IS_VERSION_SAME(MAJOR, MINOR, PATCH))
#define BBB_IS_VERSION_OLDER_THAN(MAJOR, MINOR, PATCH) (!BBB_IS_VERSION_NEWER_THAN_EQ(MAJOR, MINOR, PATCH))
#define BBB_IS_VERSION_OLDER_THAN_EQ(MAJOR, MINOR, PATCH) (!BBB_IS_VERSION_NEWER_THAN(MAJOR, MINOR, PATCH))

namespace bbb {
    using version_major_t = uint16_t;
    using version_minor_t = uint16_t;
    using version_patch_t = uint16_t;
    using version_t = uint64_t;

    constexpr version_major_t major() { return BBB_VERSION_MAJOR; };
    constexpr version_minor_t minor() { return BBB_VERSION_MINOR; };
    constexpr version_patch_t patch() { return BBB_VERSION_PATCH; };
    constexpr version_t version() { return BBB_VERSION; };
};
