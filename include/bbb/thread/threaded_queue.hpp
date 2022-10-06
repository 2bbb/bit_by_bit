/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/thread/threaded_queue.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <queue>

#include <thread>
#include <mutex>
#include <condition_variable>

namespace bbb {
	template <typename type>
	struct threaded_queue {
		using value_type = type;
		
		threaded_queue() = default;
		threaded_queue(const threaded_queue &other)
		: closed{false} 
		{
			std::lock_guard<std::mutex> lock(other.mutex);
			queue = other.queue;
		}
		threaded_queue(threaded_queue &&other)
		: closed{false} 
		{
			std::lock_guard<std::mutex> lock(other.mutex);
			queue = std::move(other.queue);
		}
		
		bool empty() const {
			std::lock_guard<std::mutex> lock(mutex);
			return queue.empty();
		}
		
		bool send(const value_type &v) {
			std::lock_guard<std::mutex> lock(mutex);
			if(closed) return false;
			queue.push(v);
			condition.notify_one();
			return true;
		}
		bool send(value_type &&v) {
			std::lock_guard<std::mutex> lock(mutex);
			if(closed) return false;
			queue.push(std::move(v));
			condition.notify_one();
			return true;
		}
		
		bool receive(value_type &v) {
			std::lock_guard<std::mutex> lock(mutex);
			if(closed) return false;
			if(queue.empty()) return false;
			std::swap(v, queue.front());
			queue.pop();
			return true;
		}
		
		bool try_receive(value_type &v, std::uint64_t waiting_for_micro_sec) {
			std::unique_lock<std::mutex> lock(mutex);
			if(closed) return false;
			if(queue.empty()) {
				condition.wait_for(lock, std::chrono::microseconds(waiting_for_micro_sec));
				if(queue.empty()) {
					return false;
				}
			}
			if(closed) return false;
			std::swap(v, queue.front());
			queue.pop();
			return true;
		}
		
		void close() {
			std::lock_guard<std::mutex> lock(mutex);
			closed = true;
			condition.notify_all();
		}
		
	private:
		std::queue<value_type> queue;
		mutable std::mutex mutex;
		std::condition_variable condition;
		bool closed;
	};
}
