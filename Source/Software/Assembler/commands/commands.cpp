#include "commands.hpp"
#include <iostream>
#include <string>
#include <cassert>

/* PUSH command */
void CommandPush::parse_arguments(std::span<std::string> arguments) {
    try {
        /* If is a number */
        constant = std::stoi(arguments[0].data());
    } catch (...) {
        /* Not a number, should be link */
        constant = arguments[0].data();
    }
}

void CommandPush::expand_command(std::vector<ICommand *> &commands, std::vector<ICommand *>::iterator it) {
    if(std::holds_alternative<std::string>(constant)) {
        /* Skip if houses link */
        return;
    }
    std::vector<ICommand *> new_commands;
    unsigned int constant_int = std::get<int>(constant);
    if(signed_constant) {
        expand_command_signed(*it, new_commands, constant_int);
    } else {
        expand_command_unsigned(*it, new_commands, constant_int);
    }
    if(new_commands.size() == 0) {
        /* No expansion, leave everything as it is */
        return;
    }
    commands.erase(it);
    commands.insert(it, new_commands.begin(), new_commands.end());
}

void CommandPush::expand_command_signed(ICommand *current_command, std::vector<ICommand *> &new_commands, int constant_int) {
    /* Make the number provided into two numbers that add to the signed constant_int */
    if((constant_int > INT8_MAX) || (constant_int < INT8_MIN)) {
       std::cerr << "Signed constant invalid" << std::endl;
        assert(false);
    }
    int8_t target_int = static_cast<int8_t>(constant_int);
    if(target_int >= 0) {
        /* No expansion required */
        return;
    }
    /* Need expanding as negative number */
    if(constant_int == -1) {
        /* Hardcoded solution for all 1s */
        new_commands.push_back(new CommandPush("PUSH", false, 5));
        new_commands.push_back(new CommandPush("PUSH", false, 51));
        new_commands.push_back(new CommandAlu("MULT", 2));
    } else {
        /* Constant not all 1s */
        unsigned int unsigned_representation = 256 - abs(constant_int);
         unsigned int offset = unsigned_representation - 127;
        new_commands.push_back(new CommandPush("PUSH", false, 127));
        new_commands.push_back(new CommandPush("PUSH", false, offset));
        new_commands.push_back(new CommandAlu("ADD", 0));
    }
}

void CommandPush::expand_command_unsigned(ICommand *current_command, std::vector<ICommand *> &new_commands, int constant_int) {
    /* Check if not over 7 bits */
    if(constant_int <= 127) {
        /* No need for expansion */
        return;
    }
    if(constant_int > UINT8_MAX) {
        std::cerr << "Constant bigger than 255" << std::endl;
        assert(false);
    }
    if(constant_int == UINT8_MAX) {
        /* Hardcoded solution */ //TODO: duplication
        new_commands.push_back(new CommandPush("PUSH", false, 5));
        new_commands.push_back(new CommandPush("PUSH", false, 51));
        new_commands.push_back(new CommandAlu("MULT", 2));
    } else {
        /* Constant not 255 */
        unsigned int offset = constant_int - 127;
        new_commands.push_back(new CommandPush("PUSH", false, 127));
        new_commands.push_back(new CommandPush("PUSH", false, offset));
        new_commands.push_back(new CommandAlu("ADD", 0));
    }

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

ICommand *CommandPush::clone(void) const {
    return new CommandPush(*this);
}

/* POP command */
void CommandPop::parse_arguments(std::span<std::string> arguments) {
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

ICommand *CommandPop::clone(void) const {
    return new CommandPop(*this);
}

/* Command basic */
uint8_t CommandBasic::assemble(void) const {
    return instruction;
    // return "xx";
}

ICommand *CommandBasic::clone(void) const {
    return new CommandBasic(*this);
}

/* Command ALU */
uint8_t CommandAlu::assemble(void) const {
    return alu_code | 0x20;
}

ICommand *CommandAlu::clone(void) const {
    return new CommandAlu(*this);
}

/* JUMP command */
void CommandJump::parse_arguments(std::span<std::string> arguments) {
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

ICommand *CommandJump::clone(void) const {
    return new CommandJump(*this);
}
