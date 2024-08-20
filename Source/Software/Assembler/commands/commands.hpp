#pragma once

#include "command_base.hpp"
#include <stdint.h>
#include <variant>

class CommandPush : public CommandBase {
    private:


        void expand_command_signed(ICommand *current_command, std::vector<ICommand *> &new_lines, int constant_int);
        void expand_command_unsigned(ICommand *current_command, std::vector<ICommand *> &new_lines, int constant_int);
    public:
        CommandPush(std::string codeword, bool signed_constant) : CommandBase(codeword, 1), signed_constant(signed_constant) {};
        CommandPush(std::string codeword, bool signed_constant, int constant) : CommandBase(codeword, 1), signed_constant(signed_constant), constant(constant) {};
        void parse_arguments(std::span<std::string> arguments) override;
        void expand_command(std::vector<ICommand *>& commands, std::vector<ICommand *>::iterator it) override;
        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;

        bool signed_constant = false;
        std::variant<int, std::string> constant = ""; //TODO: getters setters
};

class CommandPop : public CommandBase { //TODO: could be single command class with bit masking
    private:
        unsigned int amount = 0;
    public:
        CommandPop() : CommandBase("POP", 1) {};
        void parse_arguments(std::span<std::string> arguments) override;
        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;
};

class CommandBasic : public CommandBase {
    private:
        const uint8_t instruction = 0;
    public:
        CommandBasic(std::string codeword, uint8_t instruction) : CommandBase(codeword, 0), instruction(instruction) {};
        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;
};

class CommandAlu : public CommandBase {
    private:
        uint8_t alu_code = 0x00;
    public:
        CommandAlu(std::string codeword, uint8_t alu_code) : CommandBase(codeword, 0), alu_code(alu_code) {};
        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;
};

class CommandJump : public CommandBase {
    private:
        bool jump_condition = false;
    public:
        CommandJump() : CommandBase("JUMP", 1) {};
        void parse_arguments(std::span<std::string> arguments) override;
        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;
};

/* DUMMY COMMAND */
class CommandLink : public CommandBase {
    public:
        std::string link;
        CommandLink(std::string link) : CommandBase("...................", 0), link(link) {};

};
