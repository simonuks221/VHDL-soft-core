#include <string_view>
#include <string>
#include <span>

#pragma once

class ICommand {
    public:
        ICommand() = default;
        ~ICommand() = default;

        virtual std::string_view get_codeword(void) const = 0;
        virtual std::string parse_arguments(std::span<std::string_view> arguments) const = 0;
        virtual unsigned int get_argument_amount(void) const = 0;
};