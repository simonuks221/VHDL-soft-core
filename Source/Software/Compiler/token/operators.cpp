#include "tokenizer_singleton.hpp"
#include "operators.hpp"
#include <unordered_map>
#include <cassert>

BaseOperator::BaseOperator(std::string _str, unsigned int _presedence, bool _left, std::string _asm_instruction, uint8_t _properties) : IOperator(_str), presedence(_presedence), left_associative(_left), asm_instruction(_asm_instruction), properties(_properties) {
    TokenizerSingleton::get_instance().add_operator(clone());
};

BaseOperator::BaseOperator(std::string _str, unsigned int _presedence, bool _left, std::string _asm_instruction) : IOperator(_str), presedence(_presedence), left_associative(_left), asm_instruction(_asm_instruction), properties(0) {
    TokenizerSingleton::get_instance().add_operator(clone());
};

BaseOperator::BaseOperator(std::string _str, unsigned int _presedence, bool _left) : IOperator(_str), presedence(_presedence), left_associative(_left), asm_instruction(""), properties(0) {
    TokenizerSingleton::get_instance().add_operator(clone());
};

unsigned int BaseOperator::get_presedence() const {
    return presedence;
}

bool BaseOperator::get_left_associative() const {
    return left_associative;
}

eToken BaseOperator::get_type(void) {
    return eToken::Operator;
}

IToken *BaseOperator::clone(void) {
    return new BaseOperator(*this);
}

uint8_t BaseOperator::get_properties(void) const {
    return properties;
}

bool BaseOperator::has_property(eOperatorProperty property) const {
    return (properties & static_cast<uint8_t>(property)) != 0;
}

void BaseOperator::shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<IToken*> &output) const {
    BaseOperator * this_token = const_cast<BaseOperator *>(this);
    /* Regular operator found */
    while(!operator_stack.empty()) {
        IOperator* top_op = operator_stack.top();
        if((top_op->get_str() == ")") || (top_op->get_str() == "(")) {
            break;
        }

        int top_token_precedence = top_op->get_presedence(); //TODO: error handling
        if((top_token_precedence >= get_presedence()) && get_left_associative()) {
            output.push_back(top_op);
            operator_stack.pop();
        } else {
            break;
        }
    }
    /* Always push current token to top of operator stack */
    operator_stack.push(this_token);
}

std::string_view BaseOperator::assemble_instruction(void) const {
    if(asm_instruction == "") {
        /* Should not be sinthesisable */
        std::cerr << "Invalid assemble instruction token: " << get_str() << std::endl;
        assert(false);
        return "";
    }
    return asm_instruction;
}

void IgnoreOperator::shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<IToken*> &output) const {
    /* Do nothing */
}

IToken *IgnoreOperator::clone(void) {
    return new IgnoreOperator(*this);
}

std::string_view IgnoreOperator::assemble_instruction(void) const {
    /* Isn't assemblable */
    assert(false);
    return "";
}

void FunctionOperator::shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<IToken*> &output) const {
    FunctionOperator * this_token = const_cast<FunctionOperator *>(this);
    operator_stack.push(this_token);
}

IToken *FunctionOperator::clone(void) {
    return new FunctionOperator(*this);
}

std::string_view FunctionOperator::assemble_instruction(void) const {
    //TODO
    return "";
}

void ParentehsiesOperator::shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<IToken*> &output) const {
    ParentehsiesOperator * this_token = const_cast<ParentehsiesOperator *>(this);
    if(get_str() == "(") {
        /* Special case for '(' push to stack */
        operator_stack.push(this_token);
    } else if(get_str() == ")") {
        /* Special case for ')' pop everyhting from stack */
        while(!operator_stack.empty()) {
            if(operator_stack.top()->get_str() == "(") {
                operator_stack.pop();
                break;
            }
            output.push_back(operator_stack.top());
            operator_stack.pop();
        }

        FunctionOperator *function_op = nullptr;
        if(!operator_stack.empty()) {
            function_op = dynamic_cast<FunctionOperator*>(operator_stack.top());
        }
        if(function_op != nullptr) {
            output.push_back(operator_stack.top());
            operator_stack.pop();
        }
    }
}

IToken *ParentehsiesOperator::clone(void) {
    return new ParentehsiesOperator(*this);
}

std::string_view ParentehsiesOperator::assemble_instruction(void) const {
    /* Isn't assemblable */
    assert(false);
    return "";
}
