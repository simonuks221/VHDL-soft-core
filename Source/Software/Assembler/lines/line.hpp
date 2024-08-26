#pragma once

#include <string>
#include <string_view>
#include <memory>

class Line {
    private:
        unsigned int assembly_line = 0;
        unsigned int binary_line = 0;
        std::string content;
    public:
        Line(unsigned int _assembly_line, std::string &_content) : assembly_line(_assembly_line), content(_content) {};

        std::string_view get_content(void) const;
        unsigned int get_assembly_line(void) const;
        void set_content(std::string &new_content);

        static void log_err(Line &line, std::string_view message);
        static void log_err(Line *line, std::string_view message);
};
