/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * logger.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include "constants.hpp"
#include "type_utils.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

#include <chrono>
#include <ctime>
#include <iomanip>

namespace bbb {
    namespace logger {
        namespace style {
            enum class separater {
                plain = 0,
                csv = 1 << 0,
                space = 1 << 1
            };
            using separater_underlying_type = std::underlying_type_t<separater>;

            enum class header {
                plain = 0,
                timestamp = 1 << 1
            };
            using header_underlying_type = std::underlying_type_t<header>;
        }
        inline style::separater_underlying_type operator&(style::separater lhs, style::separater rhs) { return static_cast<style::separater_underlying_type>(lhs) & static_cast<style::separater_underlying_type>(rhs); }
        inline style::separater_underlying_type operator|(style::separater lhs, style::separater rhs) { return static_cast<style::separater_underlying_type>(lhs) | static_cast<style::separater_underlying_type>(rhs); }

        inline style::header_underlying_type operator&(style::header lhs, style::header rhs) { return static_cast<style::header_underlying_type>(lhs) & static_cast<style::header_underlying_type>(rhs); }
        inline style::header_underlying_type operator|(style::header lhs, style::header rhs) { return static_cast<style::header_underlying_type>(lhs) | static_cast<style::header_underlying_type>(rhs); }

        struct logger_module {
            style::separater separate_style;
            style::header header_style;
            logger_module(std::ostream *os, style::separater separate_style = style::separater::plain, style::header header_style = style::header::plain)
            : os(os)
            , separate_style(separate_style)
            , header_style(header_style) {}

            ~logger_module() { if(os != &std::cout) delete os; }

            template <typename T>
            get_type<std::enable_if<!std::is_same<T, std::ostream &(*)(std::ostream &)>::value, logger_module>> &operator<<(const T &t) {
                *os << t;
                return *this;
            }

            logger_module &operator<<(std::ostream &(*f)(std::ostream &)) {
                f(*os);
                return *this;
            }

            logger_module *header(const std::string log_level) {
                timestamp() << log_level << ": ";
                return this;
            }
            logger_module *header(const std::string log_level, const std::string name) {
                timestamp() << log_level << "[" << name << "]: ";
                return this;
            }
            void cleaning() {
                *os << "  " << std::endl;
            }

        private:
            std::ostream *os;
            inline std::ostream &timestamp() {
                if(header_style & style::header::timestamp) {
                    std::time_t t = std::time(NULL);
                    std::tm tm = *std::localtime(&t);
                    *os << std::put_time(&tm, "%Y/%m/%d %T ");
                }
                return *os;
            }
        };

        class manager {
            using enabled_map_t = std::unordered_map<std::string, bool>;
            static enabled_map_t &enabled_map() {
                static enabled_map_t m;
                return m;
            }
            inline static bool is_enabled(const std::string &name) { return (enabled_map().find(name) == enabled_map().end()) ? true : enabled_map().at(name); }

            using logger_module_map_t = std::unordered_map<std::string, logger_module *>;
            inline static logger_module_map_t &logger_map() {
                static logger_module_map_t m;
                return m;
            }
        public:
            inline static void enable(const std::string &name) { enabled_map()[name] = true; }
            inline static void disable(const std::string &name) { enabled_map()[name] = false; }

            static logger_module &default_logger_module() {
                static logger_module m(&std::cout);
                return m;
            }
            static logger_module &get_logger_module(const std::string &name) {
                auto it = logger_map().find(name);
                if(it == logger_map().end()) return default_logger_module();
                return *(it->second);
            }

            static void add_logger(const std::string &name, std::ostream *os = &std::cout) {
                logger_module_map_t::iterator it = logger_map().find(name);
                if(it != logger_map().end()) {
                    delete it->second;
                    it->second = new logger_module(os);
                } else {
                    logger_map()[name] = new logger_module(os);
                }
            }
            static void remove_logger(const std::string &name) {
                logger_module_map_t::iterator it = logger_map().find(name);
                if(it != logger_map().end()) {
                    delete it->second;
                    logger_map().erase(name);
                }
            }
        };

        struct base_logger {
            base_logger() = delete;
            base_logger(const std::string &level)
            : module(manager::default_logger_module().header(level)) {}
            base_logger(const std::string &level, const std::string &name)
            : module(manager::get_logger_module(name).header(level, name)) {}
            base_logger(const base_logger &logger)
            : module(logger.module) {}
            virtual ~base_logger() { module->cleaning(); }

            template <typename T>
            base_logger &operator<<(const T &t) {
                *module << t;
                return *this;
            };

            base_logger &operator<<(std::ostream &(*f)(std::ostream &)) {
                module->operator<<(f);
                return *this;
            }

        private:
            logger_module *module;
        };

        void add_stdout_logger(const std::string &name) {
            manager::add_logger(name);
        }

        void add_file_logger(const std::string &name, const std::string &path) {
            manager::add_logger(name, new std::ofstream(path));
        }

        void add_stringbuffer_logger(const std::string &name) {
            manager::add_logger(name, new std::stringstream(""));
        }

        struct trace : public base_logger {
            trace() : base_logger("trace") {}
            trace(const std::string &name) : base_logger("trace", name) {}
        };

        struct debug : base_logger {
            debug() : base_logger("debug") {}
            debug(const std::string &name) : base_logger("debug", name) {}
        };

        struct info : base_logger {
            info() : base_logger("info") {}
            info(const std::string &name) : base_logger("info", name) {}
        };

        struct warning : base_logger {
            warning() : base_logger("warning") {}
            warning(const std::string &name) : base_logger("warning", name) {}
        };
    };
    using namespace logger;
};