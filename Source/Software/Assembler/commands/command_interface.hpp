#include <string_view>
#include <string>
#include <span>
#include <stdint.h>

#pragma once

class ICommand {
    public:
        ICommand() = default;
        ~ICommand() = default;

        virtual std::string_view get_codeword(void) const = 0;
        virtual void parse_arguments(std::span<std::string_view> arguments) = 0;
        virtual unsigned int get_argument_amount(void) const = 0;
        virtual uint8_t assemble(void) const = 0;
};