#pragma once

#include <string>
#include <vector>
#include <unordered_map>

class Preprocessor {
    private:
        static constexpr std::string word_delimiters = " \t";
        /* Link declaration name and its corresponding line number */
        std::unordered_map<std::string, unsigned int> all_links;

        void find_all_links(std::vector<std::string> &lines);
        void replace_all_links(std::vector<std::string> &lines);
        void replace_if_link(std::string &line, size_t start, size_t end);
    public:
        Preprocessor() {};
        ~Preprocessor() = default;

        /* Proces links (like .block_end) into constants of line number.
         * Need lines without clutter (comments, empty lines) as input */
        void process_links(std::vector<std::string> &lines);
};