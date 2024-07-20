#include "keywords.hpp"

CurlyBracesKeyword::CurlyBracesKeyword(std::string _str) : Keyword(_str) {
    open = _str == "{";
}

IToken *CurlyBracesKeyword::clone(void) const {
    return new CurlyBracesKeyword(*this);
}

std::string_view CurlyBracesKeyword::assemble_instruction(void) const {
    if(open) {
        instruction = std::string("#." + std::to_string(brace_idx));
    } else {
        instruction = std::string("." + std::to_string(brace_idx));
    }

    return instruction;
}

bool CurlyBracesKeyword::get_open(void) const {
    return open;
}

unsigned int CurlyBracesKeyword::get_brace_idx(void) const {
    return brace_idx;
}

void CurlyBracesKeyword::set_brace_idx(unsigned int new_value) {
    brace_idx = new_value;
}

IToken *WhileKeyword::clone(void) const {
    return new WhileKeyword(*this);
}

std::string_view WhileKeyword::assemble_instruction(void) const {
    instruction = std::string("while jump to ." + std::to_string(brace_idx));
    return instruction;
}

unsigned int WhileKeyword::get_brace_idx(void) const {
    return brace_idx;
}

void WhileKeyword::set_brace_idx(unsigned int new_value) {
    brace_idx = new_value;
}

bool WhileKeyword::parse_for_brace(std::span<IToken *> tokens) {
    /* Search for opening brace */
    for(IToken *token : tokens) {
        if(token->get_type() != eToken::Keyword) {
            continue;
        }
        CurlyBracesKeyword *braces = dynamic_cast<CurlyBracesKeyword *>(token);
        if(braces == nullptr) {
            continue;
        }
        if(!braces->get_open()) {
            return false;
        }
        brace_idx = braces->get_brace_idx();
        return true;
    }
    return false;
}