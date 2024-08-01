#include "commands.hpp"
#include <iostream>

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
    return "FALSE JUMP";
}

std::string CommandGoto::parse_arguments(std::span<std::string_view> arguments) const {
    return "JUMP";
}

std::string CommandMoreThan::parse_arguments(std::span<std::string_view> arguments) const {
    return "MORE THAN";
}

std::string CommandAdd::parse_arguments(std::span<std::string_view> arguments) const {
    return "ADD";
}

std::string CommandLessThan::parse_arguments(std::span<std::string_view> arguments) const {
    return "LESS THAN";
}
