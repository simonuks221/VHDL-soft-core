#include "command_base.hpp"

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
        CommandIfFalseJump() : CommandBase("IF_FALSE_JUMP", 0) {};
        std::string parse_arguments(std::span<std::string_view> arguments) const override;
};

class CommandGoto : public CommandBase {
    public:
        CommandGoto() : CommandBase("GOTO", 0) {};
        std::string parse_arguments(std::span<std::string_view> arguments) const override;
};

class CommandMoreThan : public CommandBase {
    public:
        CommandMoreThan() : CommandBase("MORE_THAN", 0) {};
        std::string parse_arguments(std::span<std::string_view> arguments) const override;
};

class CommandAdd : public CommandBase {
    public:
        CommandAdd() : CommandBase("ADD", 0) {};
        std::string parse_arguments(std::span<std::string_view> arguments) const override;
};

class CommandLessThan : public CommandBase {
    public:
        CommandLessThan() : CommandBase("LESS_THAN", 0) {};
        std::string parse_arguments(std::span<std::string_view> arguments) const override;
};

