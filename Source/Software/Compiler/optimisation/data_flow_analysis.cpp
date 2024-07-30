#include "data_flow_analysis.hpp"
#include "logging.hpp"
#include <cassert>
#include <algorithm>

const std::vector<CFGBlock *> CFGBlock::get_next(void) const {
    return next;
}

const std::vector<CFGBlock *> CFGBlock::get_prev(void) const {
    return previous;
}

const std::vector<ILine *> CFGBlock::get_lines(void) const {
    return lines;
}

void CFGBlock::add_line(ILine *new_line) {
    lines.push_back(new_line);
}

void CFGBlock::add_next(CFGBlock *new_next) {
    next.push_back(new_next);
}

void CFGBlock::add_prev(CFGBlock *new_prev) {
    previous.push_back(new_prev);
}

/* Traverses node map backwards to find if token was defined */
IToken *DataFlowAnalysis::find_if_defined(const IToken *variable, const CFGBlock *start_block) const {
    if((variable == nullptr) || (start_block == nullptr)) {
        return nullptr;
    }
    for(ILine *line : start_block->get_lines()) {
        /* Check if start block contains the variable in question */
        auto it = std::find_if(line->get_variables_out().begin(), line->get_variables_out().end(), [variable](IToken* it_token) {
            if(it_token->get_type() != variable->get_type()) {
                return false;
            }
            return it_token->get_str() == variable->get_str();
        });
        if(it != line->get_variables_out().end()) {
            /* Found defined variable */
            return static_cast<IToken *>(*it);
        }
    }
    /* Variable not found in start block */
    for(CFGBlock *previous : start_block->get_prev()) {
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
        new_block->add_line(line);
        if(root == nullptr) {
            /* First block */
            root = new_block;
            last_block = new_block;
            continue;
        }
        last_block->add_next(new_block);
        new_block->add_prev(last_block);
        /* Find if all in variables were defined previously */
        for(IToken *token : line->get_variables_in()) {
            IToken *definition = find_if_defined(token, last_block);
            if(definition == nullptr) {
                /* Not defined */
                Logging::error("Can't find definition for variable: " + std::string(token->get_str()));
                assert(false);
            }
            /* Defined, replace this token with definition one */
            //line->replace_token(token, definition);
            //free(token);
            //token =
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