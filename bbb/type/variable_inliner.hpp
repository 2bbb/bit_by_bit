/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/type/variable_inliner.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#ifndef bbb_type_variable_inliner_hpp
#define bbb_type_variable_inliner_hpp

namespace bbb {
    template <typename variable_type, typename tag = variable_type>
    struct variable_inliner {
        static variable_type &get() {
            static variable_type _;
            return _;
        };
    };
};

#endif /* bbb_type_variable_inliner_hpp */
