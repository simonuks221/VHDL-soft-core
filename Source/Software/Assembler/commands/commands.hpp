#include "command_base.hpp"
#include <stdint.h>

#pragma once

class CommandPush : public CommandBase {
    public:
        CommandPush() : CommandBase("PUSH", 1) {};
        std::string parse_arguments(std::span<std::string_view> arguments) const override;

};

class CommandPop : public CommandBase {
    public:
        CommandPop() : CommandBase("POP", 0) {};
        std::string parse_arguments(std::span<std::string_view> arguments) const override;
};

class CommandSaveMem : public CommandBase {
    public:
        CommandSaveMem() : CommandBase("SAVE_MEM", 0) {};
        std::string parse_arguments(std::span<std::string_view> arguments) const override;
};

class CommandLoadMem : public CommandBase {
    public:
        CommandLoadMem() : CommandBase("LOAD_MEM", 0) {};
        std::string parse_arguments(std::span<std::string_view> arguments) const override;
};

class CommandIfFalseJump : public CommandBase {
    public:
        CommandIfFalseJump() : CommandBase("IF_FALSE_JUMP", 1) {};
        std::string parse_arguments(std::span<std::string_view> arguments) const override;
};

class CommandGoto : public CommandBase {
    public:
        CommandGoto() : CommandBase("GOTO", 1) {};
        std::string parse_arguments(std::span<std::string_view> arguments) const override;
};

class CommandMoreThan : public CommandBase {
    public:
        CommandMoreThan() : CommandBase("MORE_THAN", 0) {};
        std::string parse_arguments(std::span<std::string_view> arguments) const override;
};

class CommandAlu : public CommandBase {
    private:
        uint8_t alu_code = 0x00;
    public:
        CommandAlu(std::string codeword, uint8_t alu_code) : CommandBase(codeword, 0), alu_code(alu_code) {};
        std::string parse_arguments(std::span<std::string_view> arguments) const override;
};

