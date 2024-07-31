#include "command_base.hpp"
#include "command_parser.hpp"

CommandBase::CommandBase(std::string _codeword, unsigned int _argument_amount) : codeword(_codeword), argument_amount(_argument_amount) {
    CommandParserSingleton::get_instance().add_command(this);
};

unsigned int CommandBase::get_argument_amount(void) const {
    return argument_amount;
}

CommandParsingResult CommandBase::is_valid(std::string_view input_word) {
    // if(input_word.compare(codeword) == 0) {
    //     if(word_amount == 1) {
    //         return CommandParsingResult::End;
    //     }
    //     return CommandParsingResult::Ok;
    // }
    return CommandParsingResult::Invalid;
}

CommandParsingResult CommandBase::continue_parse(std::string_view input_word) {
    return CommandParsingResult::Invalid;
}

std::string_view CommandBase::get_codeword(void) const {
    return codeword;
}