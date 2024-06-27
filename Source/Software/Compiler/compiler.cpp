#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <cctype>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <span>
#include "token.hpp"
#include "operators.hpp"

static const std::unordered_map<std::string, IOperator> operators = {{"+", BaseOperator("+", 2, true)}, {"-", BaseOperator("-", 2, true)},
        {"*", BaseOperator("*", 3, true)}, {"/", BaseOperator("/", 3, true)}, {"^", BaseOperator("^", 4, false)}, {"(", BaseOperator("(", 0, true)},
        {")", BaseOperator("(", 0, true)}, {"sin", FunctionOperator("sin")}, {"max", FunctionOperator("max")}, {",", IgnoreOperator(",")}};


bool tokenize(std::string_view input, std::vector<std::string> &token_list) {
    std::string temp_token = "";
    for (char ch : input) {
        if(isdigit(ch) || isalnum(ch)) {
            temp_token += ch;
            continue;
        }
        std::string ch_str(1, ch);
        if(!temp_token.empty()) {
            token_list.push_back(temp_token);
            temp_token.clear();
        }
        if(operators.find(ch_str) != operators.end()) {
            /* found operator */
            token_list.push_back(ch_str);
            temp_token.clear();
        }
    }
    if(!temp_token.empty()) {
        token_list.push_back(temp_token);
    }
    return true;
}



bool convert_to_stack_ops(std::span<std::string> tokens, std::vector<std::string> &output) {
    /* Shunting yard algorithm to convert tokens to stack operations */
    std::stack<std::string> operator_stack;
    for (std::string token : tokens) {
        if(operators.find(token) == operators.end()) {
            /* Not an operator */
            output.push_back(token);
            continue;
        }
        /* Found operator */ //TODO: make into class
        if(token == ",") {
            /* Do nothing */
        } else if((token == "sin") || (token == "max")) {
            operator_stack.push(token);
        } else if(token == ")") {
            /* Special case for ')' pop everyhting from stack */
            while(!operator_stack.empty()) {
                if(operator_stack.top() == "(") {
                    operator_stack.pop();
                    break;
                }
                output.push_back(operator_stack.top());
                operator_stack.pop();
            }
            if((operator_stack.top() == "sin") || (operator_stack.top() == "max")) {
                output.push_back(operator_stack.top());
                operator_stack.pop();
                continue;
            }
        } else if(token == "(") {
            /* Special case for '(' push to stack */
            operator_stack.push(token);
            continue;
        } else {
            /* Regular operator found */
            int current_token_precedence = operators.at(token).get_presedence();
            while(!operator_stack.empty()) {
                std::string top_op = operator_stack.top();
                if((top_op == ")") || (top_op == "(")) {
                    break;
                }
                int top_token_precedence = operators.at(top_op).get_presedence(); //TODO: error handling
                if((top_token_precedence >= current_token_precedence) && (operators.at(token).get_left_associative())) {
                    output.push_back(top_op);
                    operator_stack.pop();
                } else {
                    break;
                }
            }
            /* Always push current token to top of operator stack */
            operator_stack.push(token);
        }
    }
    /* Add all operators that are left from stack */
    while(!operator_stack.empty()) {
        output.push_back(operator_stack.top());
        operator_stack.pop();
    }

    return true;
}

int main(int argc, char* argv[]) {
    std::string input = "sin(max(2,3)/3*5)";
    std::cout << "Starting" <<std::endl;
    std::vector<std::string> token_list;
    tokenize(input, token_list);
    std::cout << "Got tokens:" <<std::endl;
    for(std::string str : token_list) {
        std::cout << str << std::endl;
    }
    std::vector<std::string> stack_token_list;
    convert_to_stack_ops(token_list, stack_token_list);
    std::cout << "Got stack ops:" <<std::endl;
    for(std::string str : stack_token_list) {
        std::cout << str << std::endl;
    }
    return 0;
}