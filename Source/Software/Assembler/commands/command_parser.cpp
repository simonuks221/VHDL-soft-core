#include <iostream>
#include "command_parser.hpp"

bool CommandParser::parse_line(std::string_view line) {
    for(CommandBase *cmd : commands) {
        std::cout << "1" <<std::endl;
    }
    return true;
}

bool CommandParser::add_command(CommandBase* instance) {
    if(instance == nullptr) {
        return false;
    }
    commands.push_back(instance);
    return true;
}

CommandParser& CommandParserSingleton::get_instance() {
    static CommandParser instance;
    return instance;
}
