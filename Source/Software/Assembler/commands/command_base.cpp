#include "command_base.hpp"
#include "command_parser.hpp"

CommandBase::CommandBase(std::string _codeword) : codeword(_codeword) {
    CommandParser::add_command(this);
};

std::string_view CommandBase::get_codeword(void) const {
    return codeword;
}

bool CommandBase::parse_arguments(std::span<std::string> arguments) {
    (void)arguments;
    /* Needs to be implemented in children */
    return arguments.size() == 0;
}

bool CommandBase::expand_command(std::vector<std::unique_ptr<ICommand>> &commands, unsigned int index) {
    (void)commands;
    (void)index;
    /* Needs to be implemented in children */
    return false;
}

uint8_t CommandBase::assemble(void) const {
    /* Needs to be implemented in children */
    return 0x00;
}

ICommand *CommandBase::clone(void) const {
    return new CommandBase(*this);
}