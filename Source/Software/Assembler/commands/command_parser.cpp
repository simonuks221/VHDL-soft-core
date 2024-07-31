#include <iostream>
#include <ranges>
#include <cassert>
#include <vector>
#include "command_parser.hpp"
#include "commands.hpp"

// std::vector<CommandBase*> CommandParser::commands {static_cast<CommandBase*>(new CommandPush()), static_cast<CommandBase*>(new CommandPop())};
std::unordered_map<std::string_view, CommandBase*> CommandParser::commands;

CommandPush push_cmd;
CommandPop pop_cmd;

void CommandParser::add_command(CommandBase *new_command) {
    commands.insert_or_assign(new_command->get_codeword(), new_command);
}

CommandBase *CommandParser::try_parse_token(std::string_view token) {
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

bool CommandParser::parse_line(std::string_view line) {
    // std::string temp_token = "";
    unsigned int word_index = 0;
    CommandBase *current_command = nullptr;
    std::vector<std::string_view> words;
    for (auto word : std::views::split(line, ' ')) {
        words.emplace_back(std::string_view(&*word.begin(), std::ranges::distance(word)));
    }
    for (std::string_view curr_word : words) {
        if(curr_word.empty()) {
            return true;
        }
        /* Check if comment */
        if(curr_word[0] == '#') {
            return true;
        }
        if(word_index == 0) {
            /* First word should be command */
            current_command = try_parse_token(curr_word);
            assert(current_command != nullptr);
            if(current_command->get_argument_amount() + 1 > words.size()) {
                std::cerr << "Not enough arguemtns in line" << std::endl;
                assert(false);
            }
        }
        word_index++;
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
