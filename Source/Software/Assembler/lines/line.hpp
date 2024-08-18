#pragma once

#include <string>
#include <string_view>

class Line {
    private:
        unsigned int assembly_line = 0;
        unsigned int binary_line = 0;
        std::string content;
    public:
        Line(unsigned int assembly_line, std::string &content) : assembly_line(assembly_line), content(content) {};

        std::string_view get_content(void) const;
        unsigned int get_assembly_line(void) const;
        void set_content(std::string &new_content);
};
