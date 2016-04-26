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
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <random>
#include <algorithm>

#include <bbb/core/constants.hpp>
#include <bbb/core/type_utils.hpp>

namespace bbb {
    namespace random {
        std::random_device engine_device;
        std::uint_fast64_t device() {
            return engine_device();
        }

        std::minstd_rand engine_linear;
        std::minstd_rand &engine_default = engine_linear;

        template <typename Engine>
        void set_seed(Engine &engine, typename Engine::result_type seed) {
            engine.seed(seed);
        }

        void set_seed_fast(std::uint_fast32_t seed = device()) {
            set_seed(engine_linear, seed);
        }

        std::uint_fast32_t fast() {
            return engine_linear();
        }

        std::mt19937_64 engine_mt19937;

        void set_seed_mt(std::uint_fast32_t seed = device()) {
            set_seed(engine_mt19937, seed);
        }

        std::uint_fast32_t mt() {
            return engine_mt19937();
        }

        std::mt19937_64 engine_mt19937_64;

        void set_seed_mt64(std::uint_fast32_t seed = device()) {
            set_seed(engine_mt19937, seed);
        }

        std::uint_fast64_t mt64() {
            return engine_mt19937_64();
        }

#pragma mark floating point random function

        std::uniform_real_distribution<double> default_dist(0.0, 1.0);

        template <typename Engine>
        double random(Engine &engine) {
            return default_dist(engine);
        }

        inline double random() {
            return random(engine_default);
        }

        template <typename Engine>
        double random(double max, Engine &engine) {
            return std::uniform_real_distribution<double>(0.0, max)(engine);
        }

        inline double random(double max) {
            return random(max, engine_default);
        }

        template <typename Engine>
        double random(double min, double max, Engine &engine) {
            return std::uniform_real_distribution<double>(min, max)(engine);
        }

        inline double random(double min, double max) {
            return random(min, max, engine_default);
        }
    }

    template <typename Container>
    void shuffle(Container &v) {
        static_assert(&Container::begin, "require: begin()");
        static_assert(&Container::begin, "require: end()");
        std::shuffle(v.cbegin(), v.cend(), random::engine_mt19937);
    }
};