#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "line.hpp"

class Preprocessor {
    private:
        static constexpr std::string word_delimiters = " \t";
        /* Link declaration name and its corresponding line number */
        static std::unordered_map<std::string, unsigned int> all_links;

        static void find_all_links(std::vector<Line> &lines);
        static void replace_all_links(std::vector<Line> &lines);
        static void add_link_loads_to_jump(std::vector<Line> &lines);
        static void replace_if_link(Line &line, size_t start, size_t end);
    public:
        Preprocessor() = default;
        ~Preprocessor() = default;

        /* Proces links (like .block_end) into constants of line number.
         * Need lines without clutter (comments, empty lines) as input */
        static void process_links(std::vector<Line> &lines);
        /* Process big constants to expand the number size from 7 to 8 bits */
};