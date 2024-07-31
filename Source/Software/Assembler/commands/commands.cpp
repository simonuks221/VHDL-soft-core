#include "commands.hpp"
#include <iostream>

CommandParsingResult CommandPush::continue_parse(std::string_view input_word) {
    CommandParsingResult result = CommandParsingResult::End;
    unsigned value = 0;
    try {
        value = std::stoul(std::string(input_word));
    } catch (const std::exception& e) {
        std::cerr << "Not integer value" << std::endl;
        result = CommandParsingResult::Invalid;
    }
    return result;
}