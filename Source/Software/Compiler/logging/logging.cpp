#include "logging.hpp"

void Logging::info(std::string_view message) {
    std::cout <<"[INFO] " << message << std::endl;
}

void Logging::error(std::string_view message) {
    std::cerr <<"[ERROR] " << message << std::endl;
}

void Logging::raw(std::string_view message) {
    std::cerr << message << std::endl;
}