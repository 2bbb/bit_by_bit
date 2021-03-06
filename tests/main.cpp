/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * tests/main.cpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#include <bbb/bit_by_bit.hpp>

#include "./core/constants.hpp"
#include "./core/type_utils.hpp"

#include "./container/utility.hpp"
#include "./container/delegation.hpp"
#include "./container/iterator.hpp"
#include "./container/array.hpp"
#include "./container/reusable_array.hpp"
#include "./container/byte_array.hpp"

#include "./function/lambda_symbol.hpp"
#include "./function/direct_lambda.hpp"

#include "./thread/thread_utils.hpp"

#include "./math/math_utils.hpp"

#include "./dirty/reference.hpp"
#include "./misc/stop_watch.hpp"
#include "./misc/simple_test.hpp"

#include "thread/thread_utils.hpp"

int main(int argc, char *argv[]) {
    bbb_test(test);

    bbb_test(reusable_array)
    bbb_test(byte_array);
    bbb_test(iterator_delegation);
    bbb_test(container_delegation);
    bbb_test(array);
    bbb_test(enumerate);

    bbb_test(multithread);

    bbb_test(lambda_symbol);
    bbb_test(direct_lambda);
}