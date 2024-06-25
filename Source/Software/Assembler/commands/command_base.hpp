#include <string>
#include "command_interface.hpp"

class CommandBase : CommandInterface {
    private:
        std::string codeword;
        int word_amount;
    public:
        CommandBase(std::string _codeword, int _word_amount) : codeword(_codeword), word_amount(_word_amount) {};
        ~CommandBase() = default;
        CommandParsingResult is_valid(std::string_view input_word) override;
        CommandParsingResult continue_parse(std::string_view input_word) override;
};
