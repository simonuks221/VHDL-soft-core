#include <iostream>
#include <string_view>

#pragma once

enum class LoggingLevel {
    Info,
    Warning,
    Error
};

class Logging {
    private:
        static inline void log(LoggingLevel level, std::string_view message);
    public:
        static void info(std::string_view message);
        static void wrn(std::string_view message);
        static void err(std::string_view message);
};