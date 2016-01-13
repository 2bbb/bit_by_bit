/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * thread_utils.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include "thread/thread_utils.hpp"
#include "misc/simple_test.hpp"

bbb_test_begin_definition(multithread)

    const std::size_t num = 4;
    std::size_t sum = 0;
    bool is_run = true;
    bbb::stop_watch watch;
    watch.start();
    bbb::multithread::manager manager(num, [&sum, &is_run](std::size_t index, std::mutex &mutex) {
        while(is_run) {
            if(mutex.try_lock()) {
                sum++;
                mutex.unlock();
            }
            bbb::sleep_nanoseconds(50);
        }
    });

    while(is_run) {
        bbb::sleep_milliseconds(10);
        auto lock(manager.lock_guard());
        if(100000 < sum) {
            is_run = false;
            manager.join();
        }
    }
    watch.rap();
    std::cout << "time: " << watch.getLastRapMilliseconds() << std::endl;

bbb_test_end_definition(multithread)
