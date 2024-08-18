#include "commands.hpp"
#include <iostream>
#include <string>
#include <cassert>

/* PUSH command */
void CommandPush::parse_arguments(std::span<std::string_view> arguments) {
    try {
        /* If is a number */
        constant = std::stoi(arguments[0].data());
    } catch (...) {
        /* Not a number, should be link */
        constant = arguments[0].data();
    }
}

void CommandPush::expand_command(std::vector<Line>& lines, std::vector<Line>::iterator it) {
    if(std::holds_alternative<std::string>(constant)) {
        /* Skip if houses link */
        return;
    }
    unsigned int constant_int = std::get<int>(constant);
    /* Check if not over 7 bits */
    if(constant_int <= 127) {
        /* No need for expansion */
        return;
    }
    if(constant_int > 255) {
        std::cerr << "Constant bigger than 255 at line: " << std::to_string(it->get_assembly_line()) << std::endl;
        assert(false);
    }
    std::vector<Line> new_lines;
    lines.erase(it);
    if(constant_int == 255) {
        /* Hardcoded solution */
        new_lines.push_back(Line(it->get_assembly_line(), std::string("PUSH 5")));
        new_lines.push_back(Line(it->get_assembly_line(), std::string("PUSH 51")));
        new_lines.push_back(Line(it->get_assembly_line(), std::string("MULT")));
    } else {
        /* Constant not 255 */
        unsigned int offset = constant_int - 127;
        new_lines.push_back(Line(it->get_assembly_line(), std::string("PUSH 127")));
        new_lines.push_back(Line(it->get_assembly_line(), std::string("PUSH " + std::to_string(offset))));
        new_lines.push_back(Line(it->get_assembly_line(), std::string("ADD")));
    }
    lines.insert(it, new_lines.begin(), new_lines.end());
}

uint8_t CommandPush::assemble(void) const {
    if(std::holds_alternative<std::string>(constant)) {
        std::cerr << "Push link not resolved" << std::endl;
        assert(false);
    }
    unsigned int constant_int = std::get<int>(constant);
    if(constant_int > 127) {
        /* No need for expansion */
        std::cerr << "Push constant too big" << std::endl;
        assert(false);
    }
    return static_cast<uint8_t>(constant_int) | 0x80;
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
