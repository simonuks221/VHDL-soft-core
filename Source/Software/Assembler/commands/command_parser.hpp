#include <unordered_map>
#include <string_view>
#include <fstream>
#include <vector>
#include "command_interface.hpp"

#pragma once

class CommandParser {
    private:
        static constexpr std::string word_delimiters = " \t";
        static std::unordered_map<std::string_view, ICommand*> commands;

        static ICommand *try_parse_token(std::string_view token);
    public:
        CommandParser() = default;
        ~CommandParser() = default;

        static void add_command(ICommand *new_command);
        static bool parse_lines(std::vector<std::string> &lines, std::ofstream &binary_file);
};