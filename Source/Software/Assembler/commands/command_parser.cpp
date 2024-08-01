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
/* ALU commands */ //TODO: make alu command class
CommandMoreThan more_than_cmd;
CommandLessThan less_than_cmd;
CommandAdd add_cmd;

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

auto is_any_of(const std::string& delimiters) {
    return [delimiters](char ch) {
        return delimiters.find(ch) != std::string::npos;
    };
}

bool CommandParser::parse_line(std::string_view line, std::ofstream &binary_file) {
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
            return true;
        }
        /* Check if comment */
        if(curr_word[0] == '#' || curr_word[0] == '.') { //TODO: remove comments and tags in preprocessor
            return true;
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
        }
    }
    //     /* Check if are already parsing command */
    //     if(current_parsing_cmd != nullptr) {
    //         /* Already parsing */
    //         CommandParsingResult parsing_result = current_parsing_cmd->continue_parse(curr_word);
    //         if(parsing_result == CommandParsingResult::Invalid) {
    //             std::cerr << "Invalid parsing result at \"" << curr_word <<"\"" <<std::endl;
    //             return false;
    //         } else if (parsing_result == CommandParsingResult::End) {
    //             /* Parsed full command, reset parsing */
    //             current_parsing_cmd = nullptr;
    //         }
    //     } else {
    //         /* Currently not parsing any cmd, find a new mathcing one */
    //         CommandParsingResult parsing_result = CommandParsingResult::Invalid;
    //         for(CommandBase *cmd : commands) {
    //             parsing_result = cmd->is_valid(curr_word);
    //             if(parsing_result == CommandParsingResult::Invalid) {
    //                 continue;
    //             }
    //             if(parsing_result == CommandParsingResult::End) {
    //                 /* Found command from one word */
    //                 break;
    //             }
    //             /* Found valid command start */
    //             current_parsing_cmd = cmd;
    //             break;
    //         }
    //         if(parsing_result == CommandParsingResult::Invalid) {
    //             /* Didint't find a matching command */
    //             std::cerr << "Couldn't find a matching command at \"" << curr_word <<"\"" <<std::endl;
    //         }
    //     }
    // }
    // if(current_parsing_cmd != nullptr) {
    //     std::cerr << "Invalid amount of arguments at line" <<std::endl;
    // }
    return true;
}

CommandParser& CommandParserSingleton::get_instance() {
    static CommandParser instance;
    return instance;
}
