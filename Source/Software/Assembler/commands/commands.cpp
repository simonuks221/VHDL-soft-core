#include "commands.hpp"
#include <iostream>
#include <string>
#include <cassert>

std::string CommandPush::parse_arguments(std::span<std::string_view> arguments) const {
    return "PUSH";
}

std::string CommandPop::parse_arguments(std::span<std::string_view> arguments) const {
    return "POP";
}

std::string CommandSaveMem::parse_arguments(std::span<std::string_view> arguments) const {
    return "SAVE";
}

std::string CommandLoadMem::parse_arguments(std::span<std::string_view> arguments) const {
    return "LOAD";
}

std::string CommandIfFalseJump::parse_arguments(std::span<std::string_view> arguments) const {
    return "FALSE_JUMP";
}

std::string CommandGoto::parse_arguments(std::span<std::string_view> arguments) const {
    unsigned int jump_location = 0;
    try {
        jump_location = std::stoi(arguments[0].data());
    } catch (...) {
        std::cerr << "Failed integer conversion of: " << arguments[0] << std::endl;
        assert(false);
    }
    return std::string("JUMP " + std::to_string(jump_location));
}

std::string CommandAlu::parse_arguments(std::span<std::string_view> arguments) const {
    return std::string(get_codeword().data() + std::to_string(alu_code));
}
