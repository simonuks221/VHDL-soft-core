#include "ivt.hpp"
#include "logging.hpp"
#include <cassert>

std::array<IRQDefinitions, 1> IVT::irq_definitions({".IRQ_1"});

uint8_t IVTCommand::assemble(void) const {
    return irq_jump_location;
}

ICommand *IVTCommand::clone(void) const {
    Logging::err("IVT is not clonable");
    assert(false);
}

void IVTCommand::set_irq_jump_location(uint8_t new_location) {
    irq_jump_location = new_location;
}

void IVT::initialise(std::vector<std::unique_ptr<ICommand>> &commands) {
    for(IRQDefinitions &irq : irq_definitions) {
        commands.insert(commands.begin(), std::make_unique<IVTCommand>());
    }
}

void IVT::final_resolve_jumps(std::vector<std::unique_ptr<ICommand>> &commands) {

    unsigned int command_amount = commands.size();
    for(unsigned int irq_i = 0; irq_i < irq_definitions.size(); irq_i++) {
        bool link_found = false;
        IVTCommand *ivt_cmd = dynamic_cast<IVTCommand *>(commands[irq_i].get());
        /* Search for irq link */
        for(unsigned int cmd_i = 0; cmd_i < command_amount; cmd_i++) {
            const CommandLink *link_cmd = dynamic_cast<CommandLink *>(commands[cmd_i].get());
            if(link_cmd == nullptr) {
                continue;
            }
            if(link_cmd->link != irq_definitions[irq_i].link_name) {
                continue;
            }
            /* Correct link found */
            ivt_cmd->set_irq_jump_location(cmd_i);
            link_found = true;
            break;
        }
        if(link_found) {
            continue;
        }
        /* Link not found, set jump location to zero */
        Logging::wrn("IRQ link " + irq_definitions[irq_i].link_name + " not found");
        ivt_cmd->set_irq_jump_location(0);
    }
}