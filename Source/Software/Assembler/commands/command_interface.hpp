#include <string_view>

enum class CommandParsingResult {
    Ok, /* Expected word received */
    End,/* Expected word received, expect to be last in a series */
    Invalid /* invalid word received */
};

class CommandInterface {
    public:
        CommandInterface() = default;
        ~CommandInterface() = default;
        virtual CommandParsingResult is_valid(std::string_view input_word) = 0;
        virtual CommandParsingResult continue_parse(std::string_view input_word) = 0;
};