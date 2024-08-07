#include <iostream>
#include <ranges>
#include <cassert>
#include <vector>
#include "command_parser.hpp"
#include "commands.hpp"

std::unordered_map<std::string_view, ICommand*> CommandParser::commands;

CommandPush push_cmd;
CommandPop pop_cmd;
CommandSaveMem save_mem_cmd;
CommandLoadMem load_mem_cmd;
CommandIfFalseJump if_false_jump_cmd;
CommandGoto goto_cmd;
/* ALU commands */
CommandAlu more_than_cmd("MORE_THAN", 0x00);
CommandAlu less_than_cmd("LESS_THAN", 0x00);
CommandAlu add_cmd("ADD", 0x00);

void CommandParser::add_command(ICommand *new_command) {
    commands.insert_or_assign(new_command->get_codeword(), new_command);
}

ICommand *CommandParser::try_parse_token(std::string_view token) {
    if(token.empty()) {
        return nullptr;
    }
    if(commands.find(token) == commands.end()) {
        std::cerr << "Invalid token found: " << token << std::endl;
        assert(false);
    }
    /* Found valid command */
    return commands.at(token);
}

bool CommandParser::parse_lines(std::vector<std::string> &lines, std::ofstream &binary_file) { //TODO: span
    for(std::string_view line : lines) {
        if(line.empty()) {
            return true;
        }
        ICommand *current_command = nullptr;
        std::vector<std::string_view> words;
        /* Parse line for words */
        size_t prev = 0;
        size_t pos = 0;
        while ((pos = line.find_first_of(word_delimiters, prev)) != std::string::npos)
        {
            if (pos > prev) {
                words.push_back(line.substr(prev, pos-prev));
            }
            prev = pos+1;
        }
        if (prev < line.length()) {
            words.push_back(line.substr(prev, std::string::npos));
        }
        for(unsigned int i = 0; i < words.size(); i++) {
            std::string_view curr_word = words[i];
            if(curr_word.empty()) {
                break;
            }
            /* Check if comment */
            if(curr_word[0] == '.') { //TODO: remove comments and tags in preprocessor
                break;
            }
            if(i == 0) {
                /* First word should be command */
                current_command = try_parse_token(curr_word);
                assert(current_command != nullptr);
                if(current_command->get_argument_amount() + 1 > words.size()) {
                    std::cerr << "Not enough arguemtns in line" << std::endl;
                    assert(false);
                }
                std::span<std::string_view> arguments(words.begin()+i+1, words.begin()+i+1+current_command->get_argument_amount());
                binary_file << current_command->parse_arguments(arguments) << std::endl;
                i += current_command->get_argument_amount();
            }
        }
    }
    return true;
}
