#include "command_base.hpp"

class CommandPush : public CommandBase {
    public:
        CommandPush() : CommandBase("PUSH", 1) {};
        CommandParsingResult continue_parse(std::string_view input_word) override;
};

class CommandPop : public CommandBase {
    public:
        CommandPop() : CommandBase("POP", 0) {};
};