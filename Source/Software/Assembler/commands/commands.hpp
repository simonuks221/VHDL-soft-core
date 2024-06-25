#include "command_base.hpp"

class CommandLoad : public CommandBase {
    public:
        CommandLoad() : CommandBase("LOAD", 2) {};
        CommandParsingResult continue_parse(std::string_view input_word) override;
};

class CommandPop : public CommandBase {
    public:
        CommandPop() : CommandBase("POP", 1) {};
};