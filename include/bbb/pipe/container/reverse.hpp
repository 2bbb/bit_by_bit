/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/pipe/container/reverse.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

#include <algorithm>

namespace bbb {
    namespace pipe  {
        namespace command {
            struct reverse {
                template <typename type>
                friend inline type operator|(type val, reverse) {
                    std::reverse(val.begin(), val.end());
                    return val;
                }
                
                template <typename type>
                friend inline type &operator|=(type &val, reverse) {
                    std::reverse(val.begin(), val.end());
                    return val;
                }
            };
        };
        
        namespace {
            inline command::reverse reverse() { return {}; }
        }
    };
};