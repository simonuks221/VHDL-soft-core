#include "command_base.hpp"

class CommandLoad : CommandBase {
    public:
        CommandLoad() : CommandBase("LOAD") {};
};

class CommandPop : CommandBase {
    public:
        CommandPop() : CommandBase("POP") {};
};