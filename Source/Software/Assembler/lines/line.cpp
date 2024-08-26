#include "line.hpp"
#include "logging.hpp"

std::string_view Line::get_content(void) const {
    return content;
}

unsigned int Line::get_assembly_line(void) const {
    return assembly_line;
}

void Line::set_content(std::string &new_content) {
    content = new_content;
}

void Line::log_err(Line &line, std::string_view message) {
    Logging::err("[ASM line " + std::to_string(line.assembly_line) + "] " + message.data());
}

void Line::log_err(Line *line, std::string_view message) {
    Logging::err("[ASM line " + std::to_string(line->assembly_line) + "] " + message.data());
}