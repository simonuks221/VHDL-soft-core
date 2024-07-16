#include "data_flow_analysis.hpp"
#include <cassert>
#include <algorithm>

/* Traverses node map backwards to find if token was defined */
IToken *find_if_defined(IToken *variable, CFGBlock *start_block) {
    if((variable == nullptr) || (start_block == nullptr)) {
        return nullptr;
    }
    /* Check if start block contains the variable in question */
    auto it = std::find_if(start_block->line->get_variables_out().begin(), start_block->line->get_variables_out().end(), [variable](IToken* it_token) {
        if(it_token->get_type() != variable->get_type()) {
            return false;
        }
        return it_token->get_str() == variable->get_str();
    });
    if(it != start_block->line->get_variables_out().end()) {
        /* Found defined variable */
        return static_cast<IToken *>(*it);
    }
    /* Variable not found in start block */
    for(CFGBlock *previous : start_block->previous) {
        IToken *ret = find_if_defined(variable, previous);
        if(ret != nullptr) {
            return ret;
        }
    }
    return nullptr;
}

void DataFlowAnalysis::analyze(std::vector<ILine *> &all_lines) {
    if(all_lines.empty()) {
        return;
    }
    CFGBlock *last_block = nullptr;
    for(ILine * line : all_lines) {
        /* Construct control flow graph blocks into linked node map */
        CFGBlock *new_block = new CFGBlock();
        new_block->line = line;
        if(root == nullptr) {
            /* First block */
            root = new_block;
            last_block = new_block;
            continue;
        }
        last_block->next.push_back(new_block);
        new_block->previous.push_back(last_block);
        /* Find if all in variables were defined previously */
        for(IToken *token : line->get_variables_in()) {
            IToken *definition = find_if_defined(token, last_block);
            if(definition == nullptr) {
                /* Not defined */
                std::cerr << "Can't find definition for variable: " << token->get_str() << std::endl;
                assert(false);
            }
        }
        last_block = new_block;
        // switch(line->get_type()) {
        //     case eLine::Default: {

        //     } break;
        //     case eLine::Assignation: {

        //     } break;
        // }
    }
 }