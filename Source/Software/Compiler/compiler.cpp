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
#include "operator.hpp"

static const std::unordered_map<char, Operator> operators = {{'+', Operator('+', 2, true)}, {'-', Operator('-', 2, true)}, {'*', Operator('*', 3, true)}, {'/', Operator('/', 3, true)}, {'^', Operator('^', 4, false)}, {'(', Operator('(', 0, true)}, {')', Operator('(', 0, true)}};


bool tokenize(std::string_view input, std::vector<std::string> &token_list) {
    std::string temp_token = "";
    for (char ch : input) {
        if(isdigit(ch) || isalnum(ch)) {
            temp_token += ch;
            continue;
        }
        if(!temp_token.empty()) {
            token_list.push_back(temp_token);
            temp_token.clear();
        }
        if(operators.find(ch) != operators.end()) {
            /* found operator */
            token_list.push_back(std::string{ch});
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
        if(token.length() == 1) {
            /* Found possible operator */
            if(operators.find(token[0]) != operators.end()) {
                /* Found operator */ //TODO: make into class
                char current_operator = token[0];

                if(current_operator == ')') {
                    /* Special case for ')' pop everyhting from stack */
                    while(!operator_stack.empty()) {
                        if(operator_stack.top()[0] == '(') {
                            operator_stack.pop();
                            break;
                        }
                        output.push_back(operator_stack.top());
                        operator_stack.pop();
                    }
                    continue;
                } else if(current_operator == '(') {
                    /* Special case for '(' push to stack */
                    operator_stack.push(token);
                    continue;
                } else {
                    /* Regular operator found */
                    int current_token_precedence = operators.at(current_operator).presedence;
                    while(!operator_stack.empty()) {
                        char top_op = operator_stack.top()[0];
                        if((top_op == ')') || (top_op == '(')) {
                            break;
                        }
                        int top_token_precedence = operators.at(top_op).presedence; //TODO: error handling
                        if((top_token_precedence >= current_token_precedence) && (operators.at(current_operator).left_associative)) {
                            output.push_back(operator_stack.top());
                            operator_stack.pop();
                        } else {
                            break;
                        }
                    }
                    /* Always push current token to top of operator stack */
                    operator_stack.push(token);
                continue;
                }
            }
            /* Not an operator, fallthrough */
        }
        /* Not an operator */ //TODO: issues with multi char operators
        output.push_back(token);
    }
    /* Add all operators that are left from stack */
    while(!operator_stack.empty()) {
        output.push_back(operator_stack.top());
        operator_stack.pop();
    }

    return true;
}

int main(int argc, char* argv[]) {
    std::string input = "3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3";
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