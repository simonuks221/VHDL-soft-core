#include <string>
#include "command_interface.hpp"

class CommandBase : CommandInterface {
    private:
        std::string codeword;
        unsigned int argument_amount;
    public:
        CommandBase(std::string _codeword, unsigned int _argument_amount);
        ~CommandBase() = default;
        CommandParsingResult is_valid(std::string_view input_word) override;
        CommandParsingResult continue_parse(std::string_view input_word) override;
        std::string_view get_codeword(void) const;
        unsigned int get_argument_amount(void) const;
};
