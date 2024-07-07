#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <cctype>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <cassert>
#include <span>
#include "binary_tree/operators.hpp"
#include "binary_tree/binary_tree.hpp"
#include "optimisation/constant_folding.hpp"

/*
Possible optimisations:
1. Constant folding (http://www2.imm.dtu.dk/courses/02198/slides/exprfold/foldexpr.pdf)
2. Algebric identities
3. Common Subexpression Elimination
4. Operator Strength Reduction
5. Inlining
6. Dead Code Elimination
7. Simplifying Conditional Expressions
8. Reassociation
9. Distribution and Factoring
10. Constant Propagation
*/

static const std::unordered_map<std::string, IOperator*> operators = {{"+", new BaseOperator("+", 2, true)}, {"-", new BaseOperator("-", 2, true)},
        {"*", new BaseOperator("*", 3, true)}, {"/", new BaseOperator("/", 3, true)}, {"^", new BaseOperator("^", 4, false)}, {"(", new ParentehsiesOperator("(")},
        {")", new ParentehsiesOperator(")")}, {"sin", new FunctionOperator("sin")}, {"max", new FunctionOperator("max")}, {",", new IgnoreOperator(",")}};


bool tokenize(std::string_view input, std::vector<IToken*> &token_list) {
    std::string temp_token = "";
    for (char ch : input) {
        if(isdigit(ch) || isalnum(ch)) {
            temp_token += ch;
            continue;
        }
        std::string ch_str(1, ch);
        if(!temp_token.empty()) {
            if(operators.find(temp_token) != operators.end()) {
                /* Operator in temp_token */
                IToken *new_token = operators.at(temp_token)->clone();
                token_list.push_back(new_token);
                temp_token.clear();
            } else {
                /* No operator in temp_token */
                IToken *new_token = nullptr;
                bool is_all_num = std::all_of(temp_token.begin(), temp_token.end(), ::isdigit);
                if(is_all_num) {
                    /* All numbers - constant */
                    new_token = new Constant(temp_token);
                } else {
                    /* Variable */
                    new_token = new Variable(temp_token);
                }
                token_list.push_back(new_token);
                temp_token.clear();
            }
        }
        if(operators.find(ch_str) != operators.end()) {
            /* found operator */
            IToken *new_token = operators.at(ch_str)->clone();
            token_list.push_back(new_token);
            temp_token.clear();
        }
    }
    if(!temp_token.empty()) {
        //TODO: duplicated code
        if(operators.find(temp_token) != operators.end()) {
            /* Operator in temp_token */
            IToken *new_token = operators.at(temp_token)->clone();
            token_list.push_back(new_token);
        } else {
            /* No operator in temp_token*/
            IToken *new_token = nullptr;
            bool is_all_num = std::all_of(temp_token.begin(), temp_token.end(), ::isdigit);
            if(is_all_num) {
                /* All numbers - constant */
                new_token = new Constant(temp_token);
            } else {
                /* Variable */
                new_token = new Variable(temp_token);
            }
            token_list.push_back(new_token);
        }
    }
    return true;
}

bool convert_to_stack_ops(std::span<IToken*> tokens, std::vector<IToken*> &output) {
    /* Shunting yard algorithm to convert tokens to stack operations */
    std::stack<IOperator *> operator_stack;
    for (IToken *token : tokens) {
        if(token->get_type() != eToken::Operator) {
            /* Not an operator */
            output.push_back(token);
            continue;
        }
        IOperator *op = dynamic_cast<IOperator*>(token);
        assert(op != nullptr);
        /* Found operator */
        op->shunting_yard_action(operator_stack, output);
    }
    /* Add all operators that are left from stack */
    while(!operator_stack.empty()) {
        output.push_back(operator_stack.top());
        operator_stack.pop();
    }
    return true;
}

int main(int argc, char* argv[]) {
    std::string input = "(3+2+x+3)*5";
    std::cout << "Starting" <<std::endl;
    std::vector<IToken*> token_list;
    tokenize(input, token_list);
    std::cout << "Got tokens:" <<std::endl;
    for(IToken *token : token_list) {
        std::cout << token->get_str() << " ";
    }
    std::cout << std::endl;
    std::vector<IToken*> stack_token_list;
    convert_to_stack_ops(token_list, stack_token_list);
    std::cout << "Got stack ops:" <<std::endl;
    for(IToken *token : stack_token_list) {
        std::cout << token->get_str() << " ";
    }
    std::cout << std::endl;
    std::cout << "Got binary tree:" << std::endl;
    BinaryTree binary_tree = BinaryTree(stack_token_list);
    binary_tree.printout_all();
    ConstantFolding constant_folding = ConstantFolding();
    constant_folding.calculate(binary_tree.get_root());
    binary_tree.printout_all();
    return 0;
}