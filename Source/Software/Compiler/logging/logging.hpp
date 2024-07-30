#include <iostream>
#include <string_view>

#pragma once

class Logging {
    public:
        static void raw(std::string_view message);
        static void info(std::string_view message);
        static void error(std::string_view message);
};