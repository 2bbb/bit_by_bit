/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/math/math_utils.hpp
 *
 * author: ISHII 2bit
 * mail:   bit_by_bit@2bit.jp
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <bbb/core.hpp>

#include <random>
#include <algorithm>

namespace bbb {
    namespace random {
        namespace {
            std::random_device engine_device;
            std::uint_fast64_t device() {
                return engine_device();
            }

            std::minstd_rand engine_linear;
            std::minstd_rand &engine_default = engine_linear;

            template <typename Engine>
            inline void set_seed(Engine &engine, typename Engine::result_type seed) {
                engine.seed(seed);
            }

            inline void set_seed_fast(std::uint_fast32_t seed = device()) {
                set_seed(engine_linear, seed);
            }

            inline std::uint_fast32_t fast() {
                return engine_linear();
            }

            std::mt19937_64 engine_mt19937;

            inline void set_seed_mt(std::uint_fast32_t seed = device()) {
                set_seed(engine_mt19937, seed);
            }

            inline std::uint_fast32_t mt() {
                return engine_mt19937();
            }

            std::mt19937_64 engine_mt19937_64;

            inline void set_seed_mt64(std::uint_fast32_t seed = device()) {
                set_seed(engine_mt19937, seed);
            }

            inline std::uint_fast64_t mt64() {
                return engine_mt19937_64();
            }

#pragma mark floating point random function

            std::uniform_real_distribution<double> default_dist(0.0, 1.0);

            template <typename Engine>
            inline double random(Engine &engine) {
                return default_dist(engine);
            }

            inline double random() {
                return random(engine_default);
            }

            template <typename Engine>
            inline double random(double max, Engine &engine) {
                return std::uniform_real_distribution<double>(0.0, max)(engine);
            }

            inline double random(double max) {
                return random(max, engine_default);
            }

            template <typename Engine>
            inline double random(double min, double max, Engine &engine) {
                return std::uniform_real_distribution<double>(min, max)(engine);
            }

            inline double random(double min, double max) {
                return random(min, max, engine_default);
            }
        }
    }
    namespace {
        template <typename Container>
        inline void shuffle(Container &v) {
            static_assert(&Container::begin, "require: begin()");
            static_assert(&Container::begin, "require: end()");
            std::shuffle(v.cbegin(), v.cend(), random::engine_mt19937);
        }
    }
};