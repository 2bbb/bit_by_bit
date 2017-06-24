#include <bbb/logger.hpp>

int main() {
    bbb::log("bbb::log") << "default is info";
    
    bbb::log.verbose("bbb::log.verbose") << "verbose";
    bbb::log.info("bbb::log.info") << "info";
    
    bbb::log.set_log_level(bbb::log_level::verbose);
    bbb::log.verbose("bbb::log.verbose") << "verbose";
    bbb::log.info("bbb::log.info") << "info";
    
    bbb::log.disable();
    bbb::log.verbose() << "verbose";
    bbb::log.enable();
    bbb::slog.warning() << "log into string stream";
    std::string str = bbb::slog.text();
    bbb::log() << "this is log after slog";
    std::cout << str;
    
    {
        bbb::custom_logger<
            bbb::simple_header,
            bbb::camma_separater
        > logger;
        logger("simple header (without log_level)") << "this is custom logger";
    }
    {
        bbb::custom_logger<
            bbb::null_header,
            bbb::camma_separater
        > logger;
        logger("will trash") << "this is custom logger without header";
    }
    {
        bbb::custom_logger<
            bbb::time_header,
            bbb::camma_separater
        > logger;
        logger("time") << "this is custom logger with time";
        logger.set_header_time_format("%T");
        logger("time") << "time format is editable";
        bbb::log.set_header_time_format("%m/%d %H:%M:%S");
        bbb::log() << "bbb::log, slog, flog is too";
    }
}