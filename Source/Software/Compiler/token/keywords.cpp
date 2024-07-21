#include "keywords.hpp"
#include "operators.hpp"

CurlyBracesKeyword::CurlyBracesKeyword(std::string _str) : Keyword(_str, 0, 0, false) {
    open = _str == "{";
}

IToken *CurlyBracesKeyword::clone(void) const {
    return new CurlyBracesKeyword(*this);
}

std::string_view CurlyBracesKeyword::assemble_instruction(void) const {
    if(open) {
        instruction = std::string("." + std::to_string(brace_idx) + "start");
    } else {
        instruction = std::string("." + std::to_string(brace_idx) + "end");
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

void CurlyBracesKeyword::set_other(CurlyBracesKeyword *_other) {
    other = _other;
}

CurlyBracesKeyword * CurlyBracesKeyword::get_other(void) const {
    return other;
}

IToken *ConditionalKeyword::clone(void) const {
    return new ConditionalKeyword(*this);
}

std::string_view ConditionalKeyword::assemble_instruction(void) const {
    instruction = std::string("IF FALSE JUMP ." + std::to_string(get_start_barce()->get_brace_idx()) + "end");
    return instruction;
}

bool ConditionalKeyword::parse_for_brace(std::span<IToken *> tokens) {
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
        start_brace = braces;
        return true;
    }
    return false;
}

void ConditionalKeyword::shunting_yard_action(std::stack<IToken*> &operator_stack, std::vector<IToken*> &output, IToken *current) const {
    /* Regular operator found */
    while(!operator_stack.empty()) {
        IToken* top_token = operator_stack.top();
        if(dynamic_cast<ParentehsiesOperator *>(top_token) != nullptr) {
            /* Stop if parentheses */
             break;
        }
        int top_token_precedence = top_token->get_presedence(); //TODO: error handling
        if((top_token_precedence >= get_presedence()) && get_left_associative()) {
            output.push_back(top_token);
            operator_stack.pop();
        } else {
            break;
        }
    }
    /* Always push current token to top of operator stack */
    operator_stack.push(current);
}

bool ConditionalKeyword::get_should_repeat(void) const {
    return should_repeat;
}

CurlyBracesKeyword *ConditionalKeyword::get_start_barce(void) const {
    return start_brace;
}

IToken *GotoKeyword::clone(void) const {
    return new GotoKeyword(*this);
}

std::string_view GotoKeyword::assemble_instruction(void) const {
    instruction = std::string("GOTO ." + std::to_string(destination->get_brace_idx()) + "start");
    return instruction;
}

void GotoKeyword::set_destination(CurlyBracesKeyword *_destination) {
    destination = _destination;
}