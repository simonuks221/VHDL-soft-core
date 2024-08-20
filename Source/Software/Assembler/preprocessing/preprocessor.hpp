#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "line.hpp"
#include "commands.hpp"

class Preprocessor {
    private:
        static constexpr std::string word_delimiters = " \t";
        /* Link declaration name and its corresponding link command */
        static std::unordered_map<std::string, ICommand *> all_links;

        static void find_all_links(std::vector<ICommand *> &commands);
        static void replace_all_links(std::vector<ICommand *> &commands);
        static void add_link_loads_to_jump(std::vector<ICommand *> &commands);
        static void replace_if_link(CommandPush *command, unsigned int current_line, std::vector<ICommand *> &commands);
    public:
        Preprocessor() = default;
        ~Preprocessor() = default;

        /* Proces links (like .block_end) into constants of line number.
         * Need lines without clutter (comments, empty lines) as input */
        static void process_links(std::vector<ICommand *> &commands);
        /* Process big constants to expand the number size from 7 to 8 bits */
};