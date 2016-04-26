/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * tests/dirty/static_variable_provider.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/misc/simple_test.hpp>

#include <bbb/dirty/static_variable_provider.hpp>

struct staticker : static_value_provider {
    static int &x() {
        return get_static<int, 0>();
    }

    static const int &y() {
        return get_static_as_const<int, 1>();
    }

    static void y(int _) {
        get_static<int, 1>() = _;
    }

    static std::string &str() {
        return get_static<std::string, 0>();
    }

    static void str(const std::string &str) {
        set_static<std::string, 0>(str);
    }

    static void str(std::string &&str) {
        set_static<std::string, 0>(std::move(str));
    }
};

int test(int argc, char *argv[]) {
    std::cout << staticker::x() << std::endl;
    std::cout << staticker::y() << std::endl;
    std::cout << staticker::str() << std::endl;

    staticker::x() = 4;
    staticker::y(5);
    staticker::str() = "abc";

    std::cout << staticker::x() << std::endl;
    std::cout << staticker::y() << std::endl;
    std::cout << staticker::str() << std::endl;

    std::string str = std::string("abc");
    staticker::str(str);
    staticker::str(std::move(std::string("")));

    return EXIT_SUCCESS;
}