#include "variables_resolver.hpp"
#include "keywords.hpp"
#include "operators.hpp"
#include "logging.hpp"
#include <cassert>
#include <algorithm>

bool VariablesResolver::resolve(std::vector<ILine *> &lines) {
    unsigned int last_variable_idx = 1;
    for(ILine *line : lines) {
        for(unsigned int i = 0; i < line->get_tokens().size(); i++) {
            IToken *token = line->get_tokens()[i];
            if(token->get_type() != eToken::Variable) {
                continue;
            }
            Variable *variable = static_cast<Variable *>(token);
            assert(variable != nullptr);
            //TODO: should remake better :/
            /* Check if assignation/declaration */
            if((i == 0) && (line->get_tokens().size() >= 3)) {
                /* Variable at start, could be assignation */
                AssignOperator *assign_op = static_cast<AssignOperator *>(line->get_tokens()[1]);
                if(assign_op == nullptr) {
                    Logging::error("Invalid variable at start of line without =");
                    assert(false);
                }
                assign_op->set_variable(variable);
                variable->set_is_declaration(true);
                if(variable_map.count(variable->get_str()) > 0) {
                    /* Redeclaring an existing variable */
                    unsigned int variable_idx = variable_map.at(variable->get_str())->get_ram_location();
                    variable->set_ram_location(variable_idx);
                    continue;
                }
                /* New variable declaration received */
                variable->set_ram_location(last_variable_idx);
                last_variable_idx++;
                variable_map[variable->get_str()] = variable;
                continue;
            }
            /* Check if writing to pointer */
            if((i == 1) && (line->get_tokens().size() >= 4)) {
                if(line->get_tokens()[0]->get_str() == "&") { //TODO: move into functions
                    /* Is pointer writing */
                    AssignOperator *assign_op = static_cast<AssignOperator *>(line->get_tokens()[2]);
                    if(assign_op == nullptr) {
                        Logging::error("Invalid pointer variable at start of line without =");
                        assert(false);
                    }
                    assign_op->set_variable(variable);
                    if(variable_map.count(variable->get_str()) == 0) {
                        Logging::error("Undeclared pointer variable");
                        assert(false);
                    }
                    /* Writing to pointer value */
                    unsigned int variable_idx = variable_map.at(variable->get_str())->get_ram_location();
                    variable->set_ram_location(variable_idx);
                    variable->set_is_pointer(true);
                    continue;
                }
            }
            /* Try find old variable */
            if(variable_map.count(variable->get_str()) == 0) {
                Logging::error("Variable " + std::string(variable->get_str()) + " has not been declared");
                assert(false);
            }
            /* Already existing variable */
            unsigned int variable_idx = variable_map.at(variable->get_str())->get_ram_location();
            variable->set_ram_location(variable_idx);
        }
    }
    return true;
}

VariablesResolver &VariablesResolver::get_instance(void) {
    static VariablesResolver instance;
    return instance;
}