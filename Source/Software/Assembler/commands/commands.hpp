#pragma once

#include "command_base.hpp"
#include <stdint.h>
#include <variant>

class CommandPushDummy : public CommandBase {
    public:
        CommandPushDummy() : CommandBase("............."){};
};

class CommandPush : public CommandBase {
    private:
        void expand_command_signed(std::vector<std::unique_ptr<ICommand>> &new_lines, int constant_int);
        void expand_command_unsigned(std::vector<std::unique_ptr<ICommand>> &new_lines, int constant_int);
        bool preallocated_space = false;
    public:
        CommandPush(std::string _codeword, bool _signed_constant) : CommandBase(_codeword), signed_constant(_signed_constant) {};
        CommandPush(std::string _codeword, bool _signed_constant, std::variant<int, std::string> _constant) : CommandBase(_codeword), signed_constant(_signed_constant), constant(_constant) {};
        bool parse_arguments(std::span<std::string> arguments) override;
        bool expand_command(std::vector<std::unique_ptr<ICommand>>& commands, unsigned int index) override;
        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;

        bool link_updated = false;
        bool signed_constant = false;
        std::variant<int, std::string> constant = ""; //TODO: getters setters
        bool will_be_signed_link = false;
        bool will_be_big_link = false;
};

class CommandPop : public CommandBase { //TODO: could be single command class with bit masking
    private:
        int amount = 0;
    public:
        CommandPop() : CommandBase("POP") {};
        bool parse_arguments(std::span<std::string> arguments) override;
        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;
};

class CommandBasic : public CommandBase {
    private:
        const uint8_t instruction = 0;
        std::vector<std::variant<int, std::string>> saved_arguments;
    public:
        CommandBasic(std::string _codeword, uint8_t _instruction) : CommandBase(_codeword), instruction(_instruction) {};
        bool parse_arguments(std::span<std::string> arguments) override;
        bool expand_command(std::vector<std::unique_ptr<ICommand>>& commands, unsigned int index) override;
        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;
};

class CommandAlu : public CommandBase {
    private:
        uint8_t alu_code = 0x00;
        std::vector<std::variant<int, std::string>> saved_arguments;
    public:
        CommandAlu(std::string _codeword, uint8_t _alu_code) : CommandBase(_codeword), alu_code(_alu_code) {};
        bool parse_arguments(std::span<std::string> arguments) override;
        bool expand_command(std::vector<std::unique_ptr<ICommand>>& commands, unsigned int index) override;
        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;
};

class CommandJump : public CommandBase {
    private:
        bool jump_condition = false;
        std::vector<std::variant<int, std::string>> saved_arguments;
    public:
        CommandJump() : CommandBase("JUMP") {};
        bool parse_arguments(std::span<std::string> arguments) override;
        bool expand_command(std::vector<std::unique_ptr<ICommand>>& commands, unsigned int index) override;
        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;
};

/* DUMMY COMMAND */
class CommandLink : public CommandBase {
    public:
        std::string link;
        CommandLink(std::string &_link) : CommandBase("dummy_link"), link(_link) {};
        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;
};
