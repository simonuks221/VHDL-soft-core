#include <string>
#include <span>
#include "command_interface.hpp"

#pragma once

class CommandBase : public ICommand {
    private:
        std::string codeword;
    public:
        CommandBase(std::string _codeword);
        ~CommandBase() = default;

        std::string_view get_codeword(void) const override;
        bool parse_arguments(std::span<std::string> arguments) override;
        bool expand_command(std::vector<std::unique_ptr<ICommand>>& commands, unsigned int index) override;
        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;
};
