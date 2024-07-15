#include "line.hpp"

std::vector<IToken *> &Line::get_tokens(void) {
    return tokens;
}

std::vector<IToken *> &Line::get_variables_in(void) {
    return tokens_in;
}

std::vector<IToken *> &Line::get_variables_out(void) {
    return tokens_out;
}

eLine Line::get_type(void) {
    return eLine::Default;
}

LineAssignation::LineAssignation(std::vector<IToken *> &_tokens) : Line(_tokens) {
    /* Assign in/out variables */
    for(IToken * token : get_tokens()) {
        if(token->get_type() == eToken::Variable) {
            if(tokens_out.empty()) {
                /* First token must be the declaration one */
                tokens_out.push_back(token);
            } else {
                tokens_in.push_back(token);
            }
        }
    }
}

eLine LineAssignation::get_type(void) {
    return eLine::Assignation;
}