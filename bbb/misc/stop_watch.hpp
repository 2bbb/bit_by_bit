/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/misc/simple_test.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <chrono>

namespace bbb {
	struct stop_watch {
		void start() {
			start_ = rap_ = std::chrono::high_resolution_clock::now();
		}
		
		template <typename T = std::chrono::nanoseconds>
		typename T::rep rap() {
			rap_ = end_;
			end_ = std::chrono::high_resolution_clock::now();
			return getLastRap();
		}
		
		template <typename T = std::chrono::nanoseconds>
		typename T::rep getLastRap() const {
			return std::chrono::duration_cast<T>(end_ - rap_).count();
		}
		
		auto getLastRapMilliseconds() const 
		-> decltype(getLastRap<std::chrono::milliseconds>()) {
			return getLastRap<std::chrono::milliseconds>();
		}
		
		auto getLastRapMicroseconds() const 
		-> decltype(getLastRap<std::chrono::microseconds>()) {
			return getLastRap<std::chrono::microseconds>();
		}
		
		auto getLastRapNanoseconds() const
		-> decltype(getLastRap<>()) {
			return getLastRap<>();
		}
		
		template <typename T = std::chrono::nanoseconds>
		typename T::rep getTotal() const {
			return std::chrono::duration_cast<T>(end_ - start_).count();
		}
		
		auto getTotalMilliseconds() const 
		-> decltype(getTotal<std::chrono::milliseconds>()) {
			return getTotal<std::chrono::milliseconds>();
		}
		
		auto getTotalMicroseconds() const 
		-> decltype(getTotal<std::chrono::microseconds>()) {
			return getTotal<std::chrono::microseconds>();
		}
		
		auto getTotalNanoseconds() const
		-> decltype(getTotal<>()) {
			return getTotal<>();
		}

		decltype(std::chrono::high_resolution_clock::now()) start_, rap_, end_;
	};
};
