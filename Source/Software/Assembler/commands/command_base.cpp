#include "command_base.hpp"
#include "command_parser.hpp"

CommandParsingResult CommandBase::is_valid(std::string_view input_word) {
    if(input_word.compare(codeword) == 0) {
        if(word_amount == 1) {
            return CommandParsingResult::End;
        }
        return CommandParsingResult::Ok;
    }
    return CommandParsingResult::Invalid;
}

CommandParsingResult CommandBase::continue_parse(std::string_view input_word) {
    return CommandParsingResult::Invalid;
}