/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * main.cpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#include "bit_by_bit.hpp"

#include "./core/constants.hpp"
#include "./core/type_utils.hpp"

#include "./container/container_utils.hpp"
#include "./container/container_delegation.hpp"
#include "./container/iterator_utils.hpp"
#include "./container/reusable_array.hpp"
#include "./container/array.hpp"

#include "./function/lambda_utils.hpp"

#include "./thread/thread_utils.hpp"

#include "./math/math_utils.hpp"

#include "./misc/dirty.hpp"
#include "./misc/stop_watch.hpp"
#include "./misc/logger.hpp"
#include "./misc/simple_test.hpp"

#include "thread/thread_utils.hpp"

int main(int argc, char *argv[]) {
    bbb_test(test);
    bbb_test(logger);

    bbb_test(reusable_array)
    bbb_test(byte_array);
    bbb_test(iterator_delegation);
    bbb_test(container_delegation);
    bbb_test(array);
    bbb_test(enumerate);

    bbb_test(multithread);
    bbb_test(lambda);
}