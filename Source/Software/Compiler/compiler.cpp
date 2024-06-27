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
#include "operators.hpp"

static const std::unordered_map<std::string, IOperator*> operators = {{"+", new BaseOperator("+", 2, true)}, {"-", new BaseOperator("-", 2, true)},
        {"*", new BaseOperator("*", 3, true)}, {"/", new BaseOperator("/", 3, true)}, {"^", new BaseOperator("^", 4, false)}, {"(", new ParentehsiesOperator("(")},
        {")", new ParentehsiesOperator(")")}, {"sin", new FunctionOperator("sin")}, {"max", new FunctionOperator("max")}, {",", new IgnoreOperator(",")}};


bool tokenize(std::string_view input, std::vector<Token*> &token_list) {
    std::string temp_token = "";
    for (char ch : input) {
        if(isdigit(ch) || isalnum(ch)) {
            temp_token += ch;
            continue;
        }
        std::string ch_str(1, ch);
        if(operators.find(temp_token) != operators.end()) {
            /* Operator in temp_token */
            IOperator *new_token = operators.at(temp_token);
            token_list.push_back(new_token);
            temp_token.clear();
        } else {
            /* No operator in temp_token*/
            Token *new_token = new Token(temp_token);
            token_list.push_back(new_token);
            temp_token.clear();
        }
        if(operators.find(ch_str) != operators.end()) {
            /* found operator */
            IOperator *new_token = operators.at(ch_str);
            //Token *new_token = new Token(ch_str);//TODO: this pushes only tokens :(
            token_list.push_back(new_token);
            temp_token.clear();
        }
    }
    if(!temp_token.empty()) {
        Token *new_token = new Token(temp_token);
        token_list.push_back(new_token);
    }
    return true;
}

bool convert_to_stack_ops(std::span<Token*> tokens, std::vector<Token*> &output) {
    /* Shunting yard algorithm to convert tokens to stack operations */
    std::stack<IOperator *> operator_stack;
    for (Token *token : tokens) {
        IOperator *op = dynamic_cast<IOperator*>(token);
        if(op == nullptr) {
            /* Not an operator */
            output.push_back(token);
            continue;
        }
        op->shunting_yard_action(operator_stack, output);
        // /* Found operator */
        // BaseOperator *base = operators.at(token->get_str());
        // FunctionOperator *func = dynamic_cast<FunctionOperator *>(base);
        // //operators.at(token->get_str())->shunting_yard_action(token, operator_stack, output);
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
    std::vector<Token*> token_list;
    tokenize(input, token_list);
    std::cout << "Got tokens:" <<std::endl;
    for(Token *token : token_list) {
        std::cout << token->get_str() << std::endl;
    }
    std::vector<Token*> stack_token_list;
    convert_to_stack_ops(token_list, stack_token_list);
    std::cout << "Got stack ops:" <<std::endl;
    for(Token *token : stack_token_list) {
        std::cout << token->get_str() << std::endl;
    }
    return 0;
}