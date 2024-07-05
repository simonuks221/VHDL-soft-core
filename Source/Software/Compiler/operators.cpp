#include "operators.hpp"
#include <unordered_map>

void IgnoreOperator::shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<Token*> &output) const {
    /* Do nothing */
}

void FunctionOperator::shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<Token*> &output) const {
    FunctionOperator * this_token = const_cast<FunctionOperator *>(this);
    operator_stack.push(this_token);
}

void ParentehsiesOperator::shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<Token*> &output) const {
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

void BaseOperator::shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<Token*> &output) const {
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