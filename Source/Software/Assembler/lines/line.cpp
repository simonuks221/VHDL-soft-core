#include "line.hpp"

std::string_view Line::get_content(void) const {
    return content;
}

unsigned int Line::get_assembly_line(void) const {
    return assembly_line;
}

void Line::set_content(std::string &new_content) {
    content = new_content;
}