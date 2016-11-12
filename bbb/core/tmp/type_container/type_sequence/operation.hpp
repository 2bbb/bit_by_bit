/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/operation.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core/tmp/type_container/type_sequence/operation/push.hpp>
#include <bbb/core/tmp/type_container/type_sequence/operation/insert.hpp>
#include <bbb/core/tmp/type_container/type_sequence/operation/concat_sequence.hpp>
#include <bbb/core/tmp/type_container/type_sequence/operation/slice.hpp>
#include <bbb/core/tmp/type_container/type_sequence/operation/remove.hpp>
#include <bbb/core/tmp/type_container/type_sequence/operation/difference_sequence.hpp>
#include <bbb/core/tmp/type_container/type_sequence/operation/map.hpp>
#include <bbb/core/tmp/type_container/type_sequence/operation/reduce.hpp>
#include <bbb/core/tmp/type_container/type_sequence/operation/make_unique.hpp>
#include <bbb/core/tmp/type_container/type_sequence/operation/make_direct_product.hpp>
#include <bbb/core/tmp/type_container/type_sequence/operation/make_combination.hpp>

namespace bbb {
    using namespace type_sequence_operations;
};
