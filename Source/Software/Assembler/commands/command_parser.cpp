#include <iostream>
#include <ranges>
#include <cassert>
#include <vector>
#include "command_parser.hpp"
#include "commands.hpp"

std::unordered_map<std::string_view, ICommand*> CommandParser::commands;

/* Command declaration */
CommandPush push_unsigned_cmd("PUSH", false);
CommandPush push_signed_cmd("PUSHS", true);
CommandPop pop_cmd;
CommandAlu addition_cmd("ADD", 0x00);
CommandAlu subtraction_cmd("SUB", 0x01);
CommandAlu multiplication_cmd("MULT", 0x02);
CommandAlu shift_right_cmd("SHFT_R", 0x03);
CommandAlu shift_left_cmd("SHFT_L", 0x04);
CommandAlu or_cmd("OR", 0x05);
CommandAlu and_cmd("AND", 0x06);
CommandAlu xor_cmd("XOR", 0x07);

CommandBasic store_cmd("STORE", 0x40);
CommandBasic load_cmd("LOAD", 0x41);
CommandJump jump_cmd;


void CommandParser::add_command(ICommand *new_command) {
    commands.insert_or_assign(new_command->get_codeword(), new_command);
}

std::unique_ptr<ICommand> CommandParser::try_parse_token(std::string_view token) {
    if(token.empty()) {
        return nullptr;
    }
    if(commands.find(token) == commands.end()) {
        std::cerr << "Invalid token found: " << token << std::endl;
        assert(false);
    }
    /* Found valid command */
    std::unique_ptr<ICommand> new_cmd(commands.at(token)->clone());
    return new_cmd;
}

std::vector<std::string> CommandParser::parse_words(std::unique_ptr<Line> &line) {
    std::vector<std::string> words;
    std::string line_content = line->get_content().data();
    if(line_content.empty()) {
        return words;
    }
    /* Parse line for words */
    size_t prev = 0;
    size_t pos = 0;
    while ((pos = line_content.find_first_of(word_delimiters, prev)) != std::string::npos)
    {
        if (pos > prev) {
            words.push_back(line_content.substr(prev, pos-prev));
        }
        prev = pos+1;
    }
    if (prev < line_content.length()) {
        words.push_back(line_content.substr(prev, std::string::npos));
    }
    return words;
}

bool CommandParser::assemble_commands(std::vector<std::unique_ptr<ICommand>> &commands, std::ofstream &binary_file) { //TODO: span
    for(const std::unique_ptr<ICommand> &command : commands) {
        uint8_t cmd = command->assemble();
        char buffer[3];
        std::sprintf(buffer, "%02x", cmd);
        binary_file << std::string(buffer) << std::endl;
    }
    return true;
}

bool CommandParser::parse_commands(std::vector<std::unique_ptr<Line>> &lines, std::vector<std::unique_ptr<ICommand>> &commands) {
    for(std::unique_ptr<Line> &line : lines) {
        std::vector<std::string> words = parse_words(line);
        std::unique_ptr<ICommand> current_command = nullptr;
        for(unsigned int i = 0; i < words.size(); i++) {
            std::string_view curr_word = words[i];
            if(curr_word.empty()) {
                break;
            }
            /* Check if link */
            if(curr_word[0] == '.') {
                std::string link_string = curr_word.data();
                std::unique_ptr<CommandLink> link = std::make_unique<CommandLink>(link_string);
                commands.push_back(std::move(link));
                break;
            }
            if(i == 0) {
                /* First word should be command */
                current_command = std::move(try_parse_token(curr_word));
                assert(current_command != nullptr);
                if(current_command->get_argument_amount() + 1 > words.size()) {
                    std::cerr << "Not enough arguments in line" << std::endl;
                    assert(false);
                }
                std::span<std::string> arguments(words.begin()+i+1, words.begin()+i+1+current_command->get_argument_amount());
                current_command->parse_arguments(arguments);
                i += current_command->get_argument_amount();
                commands.push_back(std::move(current_command));
            }
        }
    }
    return true;
}

bool CommandParser::expand_commands(std::vector<std::unique_ptr<ICommand>> &commands) {
    for(unsigned int line_i = 0; line_i < commands.size(); line_i++) {
        commands[line_i]->expand_command(commands, line_i);
    }
    return true;
}
