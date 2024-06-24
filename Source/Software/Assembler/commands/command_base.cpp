#include "command_base.hpp"
#include "command_parser.hpp"

CommandBase::CommandBase(std::string _codeword) : codeword(_codeword) {
  CommandParser &command_parser = CommandParserSingleton::get_instance();
  command_parser.add_command(this);
}

bool CommandBase::is_valid(std::string_view input) {
    return true;
}