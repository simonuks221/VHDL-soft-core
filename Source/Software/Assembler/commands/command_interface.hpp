#include <string_view>
#include <string>
#include <span>
#include <vector>
#include <stdint.h>
#include "line.hpp"

#pragma once

class ICommand {
    public:
        ICommand() = default;
        ~ICommand() = default;

        virtual std::string_view get_codeword(void) const = 0;
        virtual void parse_arguments(std::span<std::string> arguments) = 0;
        virtual void expand_command(std::vector<ICommand *>& lines, std::vector<ICommand *>::iterator it) = 0;
        virtual unsigned int get_argument_amount(void) const = 0;
        virtual uint8_t assemble(void) const = 0;

        virtual ICommand *clone(void) const = 0;
};