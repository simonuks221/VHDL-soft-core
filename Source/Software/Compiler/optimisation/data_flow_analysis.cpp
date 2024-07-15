#include "data_flow_analysis.hpp"
#include <cassert>
#include <algorithm>

bool find_if_defined(IToken *token, ILine *token_line, std::vector<ILine *> &all_lines) {
    for(ILine * line : all_lines) {
        if(line == token_line) {
            /* Reached token line, end */
            return false;
        }

        auto it = std::find_if(line->get_variables_out().begin(), line->get_variables_out().end(), [token](IToken* it_token) {
            if(it_token->get_type() != token->get_type()) {
                return false;
            }
            return it_token->get_str() == token->get_str();
        });

        if(it != line->get_variables_out().end()) {
            /* Found defined variable */
            return true;
        }
    }
    return false;
}

void DataFlowAnalysis::analyze(std::vector<ILine *> &all_lines) {
    for(ILine * line : all_lines) {
        /* Find if all in variables were defined previously */
        for(IToken * token : line->get_variables_in()) {
            if(!find_if_defined(token, line, all_lines)) {
                std::cerr << "Can't find definition for variable: " << token->get_str() << std::endl;
                assert(false);
            }
        }
        //CFGBlock new_block;
        switch(line->get_type()) {
            case eLine::Default: {

            } break;
            case eLine::Assignation: {

            } break;
        }
        //blocks.push_back(new_block);
    }
}