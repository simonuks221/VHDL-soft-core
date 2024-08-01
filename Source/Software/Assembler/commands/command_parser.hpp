#include <unordered_map>
#include <string_view>
#include <fstream>
#include "command_interface.hpp"

#pragma once

class CommandParser {
    private:
        static constexpr std::string word_delimiters = " \t";
        static std::unordered_map<std::string_view, ICommand*> commands;

        ICommand *try_parse_token(std::string_view token);
    public:
        CommandParser() = default;
        ~CommandParser() = default;

        void add_command(ICommand *new_command);
        bool parse_line(std::string_view line, std::ofstream &binary_file);
};

class CommandParserSingleton {
    public:
        /* Disallow copying and assigning */
        CommandParserSingleton(CommandParserSingleton &other) = delete;
        void operator=(const CommandParserSingleton &) = delete;
        CommandParserSingleton() = default;
        ~CommandParserSingleton() = default;
        static CommandParser & get_instance();
};