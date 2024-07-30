#include "tokenizer.hpp"
#include "operators.hpp"
#include <unordered_map>
#include <cassert>

eToken BaseOperator::get_type(void) const {
    return eToken::Operator;
}

IToken *BaseOperator::clone(void) const {
    return new BaseOperator(*this);
}

uint8_t BaseOperator::get_properties(void) const {
    return properties;
}

bool BaseOperator::has_property(eOperatorProperty property) const {
    return (properties & static_cast<uint8_t>(property)) != 0;
}

void BaseOperator::shunting_yard_action(std::stack<IToken*> &operator_stack, std::vector<IToken*> &output, IToken *current) const {
    /* Regular operator found */
    while(!operator_stack.empty()) {
        IToken* top_token = operator_stack.top();
        if((top_token->get_str() == ")") || (top_token->get_str() == "(")) { //TODO: hardcode
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

std::string_view BaseOperator::assemble_instruction(void) const {
    if(asm_instruction == "") {
        /* Should not be sinthesisable */
        std::cerr << "Invalid assemble instruction token: " << get_str() << std::endl;
        assert(false);
        return "";
    }
    return asm_instruction;
}

void IgnoreOperator::shunting_yard_action(std::stack<IToken*> &operator_stack, std::vector<IToken*> &output, IToken *current) const {
    /* Do nothing */
}

IToken *IgnoreOperator::clone(void) const {
    return new IgnoreOperator(*this);
}

void FunctionOperator::shunting_yard_action(std::stack<IToken*> &operator_stack, std::vector<IToken*> &output, IToken *current) const {
    operator_stack.push(current);
}

IToken *FunctionOperator::clone(void) const {
    return new FunctionOperator(*this);
}

std::string_view FunctionOperator::assemble_instruction(void) const {
    //TODO
    return "";
}

void ParentehsiesOperator::shunting_yard_action(std::stack<IToken*> &operator_stack, std::vector<IToken*> &output, IToken *current) const {
    if(get_str() == "(") {
        /* Special case for '(' push to stack */
        operator_stack.push(current);
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
    } else {
        std::cerr << "Invalid parantheses operator: " << get_str() << std::endl;
        assert(false);
    }
}

IToken *ParentehsiesOperator::clone(void) const {
    return new ParentehsiesOperator(*this);
}

/* Assign Operator */

IToken *AssignOperator::clone(void) const {
    return new AssignOperator(*this);
}

void AssignOperator::set_variable(Variable *new_variable) {
    variable = new_variable;
}

Variable *AssignOperator::set_variable(void) {
    return variable;
}

std::string_view AssignOperator::assemble_instruction(void) const {
    if(variable == nullptr) {
        std::cerr << "Assign operator variable not set" << std::endl;
        assert(false);
    }
    /* Push location only if not pointer */
    if(!variable->get_is_pointer()) {
        instruction = std::string("PUSH " + std::to_string(variable->get_ram_location())  + "\t#load " +  std::string(variable->get_str()) + " var loc\n");
    }
    instruction = std::string(instruction + "SAVE_MEM\t#save " + std::string(variable->get_str()) + " var");
    return instruction;
}