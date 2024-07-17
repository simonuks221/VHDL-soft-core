#include "line.hpp"

Line::Line(std::vector<IToken *> &_tokens) : tokens(_tokens) {  //TODO: do not copy token vector
    update_tokens_in_out();
}

std::vector<IToken *> &Line::get_tokens(void) {
    return tokens;
}

std::vector<IToken *> &Line::get_variables_in(void) {
    return tokens_in;
}

std::vector<IToken *> &Line::get_variables_out(void) {
    return tokens_out;
}

void Line::replace_token(IToken *new_token, unsigned int index) {
    if(index >= tokens.size()) {
        return;
    }
    free(tokens[index]);
    tokens[index] = new_token;
    update_tokens_in_out();
}

void Line::replace_token(IToken *old_token, IToken *new_token) {
    unsigned int tokens_amount = tokens.size();
    for(unsigned int i = 0; i < tokens_amount; i++) {
        if(tokens[i] == old_token) {
            free(tokens[i]);
            tokens[i] = new_token;
            update_tokens_in_out();
            return;
        }
    }
}

void Line::update_tokens_in_out(void) {
    /* Should be implemented in children */
    //TODO: remove
    /* Assign in/out variables */
    for(IToken * token : tokens) {
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

eLine Line::get_type(void) const {
    return eLine::Default;
}

LineAssignation::LineAssignation(std::vector<IToken *> &_tokens) : Line(_tokens) {

}

void LineAssignation::update_tokens_in_out(void) {
    /* Assign in/out variables */
    for(IToken * token : tokens) {
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

eLine LineAssignation::get_type(void) const {
    return eLine::Assignation;
}