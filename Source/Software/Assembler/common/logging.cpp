#include "logging.hpp"

void Logging::log(LoggingLevel log_level, std::string_view message) {
    std::string prefix;
    switch(log_level) {
        case LoggingLevel::Info: {
            std::cout << "[Info] ";
        } break;
        case LoggingLevel::Warning: {
            std::cout << "[Warning] ";
        } break;
        case LoggingLevel::Error: {
            std::cout << "[Error] ";
        } break;
    }
    std::cout << message << std::endl;
}

void Logging::err(std::string_view message) {
    Logging::log(LoggingLevel::Error, message);
}

void Logging::info(std::string_view message) {
    Logging::log(LoggingLevel::Info, message);
}

void Logging::wrn(std::string_view message) {
    Logging::log(LoggingLevel::Warning, message);
}