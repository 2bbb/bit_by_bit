/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/thread/thread_utils.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <thread>
#include <mutex>

#include <chrono>
#include <functional>

#include <vector>

#include <bbb/core.hpp>

namespace bbb {
    void sleep_seconds(double sec) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(sec * 1000.0)));
    }

    void sleep_milliseconds(double msec) {
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long long>(msec * 1000.0)));
    }

    void sleep_microseconds(double usec) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(static_cast<long long>(usec * 1000.0)));
    }

    void sleep_nanoseconds(double nsec) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(static_cast<long long>(nsec)));
    }

    inline void sleep(double sec) {
        sleep_seconds(sec);
    }

    namespace multithread {
        using process = std::function<void(std::size_t index, std::mutex &mutex)>;

        class manager {
            const std::size_t size;
            std::vector<std::thread> threads;
            std::mutex mutex;
            multithread::process process;

            std::function<void()> create_process(std::size_t index) {
                return [index, this] { process(index, mutex); };
            }

        public:
            manager(std::size_t size, multithread::process process)
            : size(size)
            , process(process) {
                threads.reserve(size);
                for(std::size_t i = 0; i < size; i++) {
                    threads.push_back(std::thread(create_process(i)));
                }
            }

            void join() {
                for(auto &thread : threads) {
                    if (thread.joinable()) thread.join();
                }
            }

            void lock() {
                mutex.lock();
            }

            bool try_lock() {
                return mutex.try_lock();
            }

            void unlock() {
                mutex.unlock();
            }

            std::unique_lock<std::mutex> lock_guard() {
                return std::unique_lock<std::mutex>(mutex);
            }

            virtual ~manager() {
                join();
            }

            manager(const manager &) = delete;
            manager &operator=(const manager &) = delete;
        };
    }
};