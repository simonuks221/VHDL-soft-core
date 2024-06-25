#include <iostream>
#include <ranges>
#include "command_parser.hpp"
#include "commands.hpp"

std::vector<CommandBase*> CommandParser::commands {static_cast<CommandBase*>(new CommandLoad()), static_cast<CommandBase*>(new CommandPop())};

bool CommandParser::parse_line(std::string_view line) {
    CommandBase *current_parsing_cmd = nullptr;
    for (auto word : std::views::split(line, ' ')) {
        std::string_view curr_word = std::string_view(&*word.begin(), std::ranges::distance(word));

        /* Check if are already parsing command */
        if(current_parsing_cmd != nullptr) {
            /* Already parsing */
            CommandParsingResult parsing_result = current_parsing_cmd->continue_parse(curr_word);
            if(parsing_result == CommandParsingResult::Invalid) {
                std::cerr << "Invalid parsing result at \"" << curr_word <<"\"" <<std::endl;
                return false;
            } else if (parsing_result == CommandParsingResult::End) {
                /* Parsed full command, reset parsing */
                current_parsing_cmd = nullptr;
            }
        } else {
            /* Currently not parsing any cmd, find a new mathcing one */
            CommandParsingResult parsing_result = CommandParsingResult::Invalid;
            for(CommandBase *cmd : commands) {
                parsing_result = cmd->is_valid(curr_word);
                if(parsing_result == CommandParsingResult::Invalid) {
                    continue;
                }
                if(parsing_result == CommandParsingResult::End) {
                    /* Found command from one word */
                    break;
                }
                /* Found valid command start */
                current_parsing_cmd = cmd;
                break;
            }
            if(parsing_result == CommandParsingResult::Invalid) {
                /* Didint't find a matching command */
                std::cerr << "Couldn't find a matching command at \"" << curr_word <<"\"" <<std::endl;
            }
        }
    }
    if(current_parsing_cmd != nullptr) {
        std::cerr << "Invalid amount of arguments at line" <<std::endl;
    }
    return true;
}

CommandParser& CommandParserSingleton::get_instance() {
    static CommandParser instance;
    return instance;
}
