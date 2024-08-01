#include "command_base.hpp"
#include "command_parser.hpp"

CommandBase::CommandBase(std::string _codeword, unsigned int _argument_amount) : codeword(_codeword), argument_amount(_argument_amount) {
    CommandParser::add_command(this);
};

unsigned int CommandBase::get_argument_amount(void) const {
    return argument_amount;
}

std::string_view CommandBase::get_codeword(void) const {
    return codeword;
}