#include "commands.hpp"
#include <iostream>
#include <string>
#include <cassert>

/* PUSH command */
void CommandPush::parse_arguments(std::span<std::string_view> arguments) {
    try {
        constant = std::stoi(arguments[0].data());
    } catch (...) {
        std::cerr << "Failed integer conversion of: " << arguments[0] << std::endl;
        assert(false);
    }
    /* Check if not over 7 bits */
    if(constant > 127) {
        std::cerr << "Constant too big: " << std::to_string(constant) << std::endl;
        assert(false);
    }
}

uint8_t CommandPush::assemble(void) const {
    return static_cast<uint8_t>(constant) | 0x80;
}

/* POP command */
void CommandPop::parse_arguments(std::span<std::string_view> arguments) {
    try {
        amount = std::stoi(arguments[0].data());
    } catch (...) {
        std::cerr << "Failed integer conversion of: " << arguments[0] << std::endl;
        assert(false);
    }
    /* Check if not over 4 bits */
    if(amount > 15) {
        std::cerr << "Amount too big: " << std::to_string(amount) << std::endl;
        assert(false);
    }
}

uint8_t CommandPop::assemble(void) const {
    return static_cast<uint8_t>(amount);
}

/* Command basic */
uint8_t CommandBasic::assemble(void) const {
    return instruction;
    // return "xx";
}

/* Command ALU */
uint8_t CommandAlu::assemble(void) const {
    return alu_code | 0x20;
}

/* JUMP command */
void CommandJump::parse_arguments(std::span<std::string_view> arguments) {
    unsigned int arguemnt_1 = 0;
    try {
        arguemnt_1 = std::stoi(arguments[0].data());
    } catch (...) {
        std::cerr << "Failed integer conversion of: " << arguments[0] << std::endl;
        assert(false);
    }
    if((arguemnt_1 != 0) && (arguemnt_1 != 1)) {
        std::cerr << "Invalid jump condition " << std::endl;
        assert(false);
    }
    jump_condition = static_cast<bool>(arguemnt_1);
}

uint8_t CommandJump::assemble(void) const {
    return 0x60 | static_cast<uint8_t>(jump_condition);
}
