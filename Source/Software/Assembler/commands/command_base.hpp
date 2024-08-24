#include <string>
#include <span>
#include "command_interface.hpp"

#pragma once

class CommandBase : public ICommand {
    private:
        std::string codeword;
        unsigned int argument_amount;
    public:
        CommandBase(std::string _codeword, unsigned int _argument_amount);
        ~CommandBase() = default;

        std::string_view get_codeword(void) const override;
        void parse_arguments(std::span<std::string> arguments) override;
        bool expand_command(std::vector<std::unique_ptr<ICommand>>& commands, unsigned int index) override;
        unsigned int get_argument_amount(void) const override;
        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;
};
