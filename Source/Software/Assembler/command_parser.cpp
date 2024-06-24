#include "command_parser.hpp"

bool CommandParser::parse_line(std::string_view line) {
    return true;
}

void CommandParserSingleton::do_stuff() {

}
CommandParser& CommandParserSingleton::get_instance() {
    static CommandParser instance;
    return instance;
}
