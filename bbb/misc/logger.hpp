/* **** **** **** **** **** **** **** **** *
 *
 *         _/        _/        _/
 *        _/_/_/    _/_/_/    _/_/_/
 *       _/    _/  _/    _/  _/    _/
 *      _/    _/  _/    _/  _/    _/
 *     _/_/_/    _/_/_/    _/_/_/
 *
 * bit by bit
 * bbb/misc/logger.hpp
 *
 * author: ISHII 2bit
 * mail:   2bit@backspace.tokyo
 *
 * **** **** **** **** **** **** **** **** */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

#include <chrono>
#include <ctime>
#include <iomanip>

#include <bbb/core.hpp>

namespace bbb {
    namespace logger {
        namespace style {
            enum class header {
                plain = 0,
                timestamp = 1 << 1
            };
            using header_underlying_type = typename std::underlying_type<header>::type;

            enum class separater {
                plain = 0,
                csv = 1 << 0,
                space = 1 << 1
            };
            using separater_underlying_type = typename std::underlying_type<separater>::type;
        }

        inline style::separater operator&(style::separater lhs, style::separater rhs) { return static_cast<style::separater>(static_cast<style::separater_underlying_type>(lhs) & static_cast<style::separater_underlying_type>(rhs)); }
        inline style::separater operator|(style::separater lhs, style::separater rhs) { return static_cast<style::separater>(static_cast<style::separater_underlying_type>(lhs) | static_cast<style::separater_underlying_type>(rhs)); }

        inline style::header operator&(style::header lhs, style::header rhs) { return static_cast<style::header>(static_cast<style::header_underlying_type>(lhs) & static_cast<style::header_underlying_type>(rhs)); }
        inline style::header operator|(style::header lhs, style::header rhs) { return static_cast<style::header>(static_cast<style::header_underlying_type>(lhs) | static_cast<style::header_underlying_type>(rhs)); }

        struct logger_separate_module;

        struct logger_header_module {
            logger_header_module(std::ostream *os, logger_separate_module &separate_module, style::header header_style)
            : os(os)
            , separate_module(separate_module)
            , header_style(header_style) {}

            template <typename T>
            get_type<std::enable_if<!std::is_same<T, std::ostream &(*)(std::ostream &)>::value, logger_separate_module>> &operator<<(const T &t)
            {
                header() << t;
                return separate_module;
            }

            logger_separate_module &operator<<(std::ostream &(*f)(std::ostream &)) {
                f(*os);
                return separate_module;
            }

            inline std::ostream &header() {
                timestamp();
                return *os;
            }

            inline std::ostream &timestamp() {
                if((header_style & style::header::timestamp) == style::header::timestamp) {
                    std::time_t t = std::time(NULL);
                    std::tm tm = *std::localtime(&t);
                    *os << std::put_time(&tm, "[%Y/%m/%d %T] ");
                }
                return *os;
            }

        private:
            logger_separate_module &separate_module;
            std::ostream *os;
            style::header header_style;
        };

        struct logger_separate_module {
            logger_separate_module(std::ostream *os, style::separater separate_style)
            : os(os)
            , separate_style(separate_style) {}

            template <typename T>
            get_type<std::enable_if<!std::is_same<T, std::ostream &(*)(std::ostream &)>::value, logger_separate_module>> &operator<<(const T &t) {
                separater() << t;
                return *this;
            }

            logger_separate_module &operator<<(std::ostream &(*f)(std::ostream &)) {
                f(*os);
                return *this;
            }

            inline std::ostream &separater() {
                return *os << (((separate_style & style::separater::csv) == style::separater::csv) ? "," : "") << (((separate_style & style::separater::space) == style::separater::space) ? " " : "");
            }

            inline void clean() { *os << std::endl; }
        private:
            std::ostream *os;
            style::separater separate_style;
        };

        struct logger_module {
            style::separater separate_style;
            style::header header_style;
            logger_module(std::ostream *os, style::separater separate_style = style::separater::plain, style::header header_style = style::header::plain)
            : os(os)
            , separater(os, separate_style)
            , header(os, separater, header_style) {}

            ~logger_module() { if(os != &std::cout) delete os; }

            template <typename T>
            logger_separate_module &operator<<(const T &t) {
                return separater << t;
            }

            inline logger_module &head(const std::string &str) {
                header << str;
                return *this;
            }
            inline void clean() {
                separater.clean();
            }

        private:
            // don't change declare order. initialization order is same to declaration order
            std::ostream *os;
            logger_separate_module separater;
            logger_header_module header;
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

            static void add_logger(const std::string &name,
                                   std::ostream *os = &std::cout,
                                   style::separater separater = get_default_separater_style(),
                                   style::header header = get_default_header_style())
            {
                logger_module_map_t::iterator it = logger_map().find(name);
                if(it != logger_map().end()) {
                    delete it->second;
                    it->second = new logger_module(os, separater, header);
                } else {
                    logger_map()[name] = new logger_module(os, separater, header);
                }
            }

            static void remove_logger(const std::string &name) {
                logger_module_map_t::iterator it = logger_map().find(name);
                if(it != logger_map().end()) {
                    delete it->second;
                    logger_map().erase(name);
                }
            }

            static style::header &get_default_header_style() {
                static style::header head = style::header::plain;
                return head;
            }

            static void set_default_header_style(style::header header) {
                get_default_header_style() = header;
            }

            static style::separater &get_default_separater_style() {
                static style::separater sep = style::separater::plain;
                return sep;
            }

            static void set_default_separater_style(style::separater separater) {
                get_default_separater_style() = separater;
            }
        };

        struct base_logger {
            base_logger() = delete;
            base_logger(const std::string &level)
            : module(manager::default_logger_module().head(level + ": ")) {}
            base_logger(const std::string &level, const std::string &name)
            : module(manager::get_logger_module(name).head(level + "[" + name + "]: ")) {}
            base_logger(const base_logger &logger)
            : module(logger.module) {}
            virtual ~base_logger() { module.clean(); }

            template <typename T>
            logger_separate_module &operator<<(const T &t) {
                return module << t;
            };

        private:
            logger_module &module;
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

