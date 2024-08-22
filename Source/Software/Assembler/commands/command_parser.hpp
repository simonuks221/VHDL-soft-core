#pragma once

#include <unordered_map>
#include <string_view>
#include <fstream>
#include <vector>
#include "command_interface.hpp"
#include "line.hpp"

class CommandParser {
    private:
        static constexpr std::string word_delimiters = " \t";
        static std::unordered_map<std::string_view, ICommand*> commands;
        static std::vector<std::string_view> all_command_names;

        static std::unique_ptr<ICommand> try_parse_token(std::string_view token);

        static std::vector<std::string> parse_words(std::unique_ptr<Line> &line);
    public:
        CommandParser() = default;
        ~CommandParser() = default;

        static void add_command(ICommand *new_command);
        static bool assemble_commands(std::vector<std::unique_ptr<ICommand>> &commands, std::ofstream &binary_file);
        static bool parse_commands(std::vector<std::unique_ptr<Line>> &lines, std::vector<std::unique_ptr<ICommand>> &commands);
        static bool expand_commands(std::vector<std::unique_ptr<ICommand>> &commands);
};