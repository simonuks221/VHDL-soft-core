#pragma once

#include "commands.hpp"

class IVTCommand : public CommandBase {
    private:
        uint8_t irq_jump_location = 0;
    public:
        IVTCommand() : CommandBase("...IVTCommand...") {}
        ~IVTCommand() = default;

        uint8_t assemble(void) const override;
        ICommand *clone(void) const override;

        void set_irq_jump_location(uint8_t new_location);
};

class IRQDefinitions {
    public:
        std::string link_name;
};

class IVT {
    private:
        static std::array<IRQDefinitions, 1> irq_definitions;
    public:
        IVT() = default;
        ~IVT() = default;

        static void initialise(std::vector<std::unique_ptr<ICommand>> &commands);
        static void final_resolve_jumps(std::vector<std::unique_ptr<ICommand>> &commands);
};