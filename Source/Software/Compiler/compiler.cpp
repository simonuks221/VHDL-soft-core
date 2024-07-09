#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include <cctype>
#include <stack>
#include <cassert>
#include <span>
#include "token/operators.hpp"
#include "token/tokenizer.hpp"
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
    std::string input = "(a+2)*5+2+(a+2)*3";
    std::cout << "Starting" <<std::endl;
    std::vector<IToken*> token_list;
    Tokenizer tokenizer = Tokenizer();
    tokenizer.tokenize(input, token_list);
    std::cout << "Got tokens:" <<std::endl;
    for(IToken *token : token_list) {
        std::cout << *token << " ";
    }
    std::cout << std::endl;
    std::vector<IToken*> stack_token_list;
    convert_to_stack_ops(token_list, stack_token_list);
    std::cout << "Got stack ops:" <<std::endl;
    for(IToken *token : stack_token_list) {
        std::cout << *token << " ";
    }
    std::cout << std::endl;
    std::cout << "Got binary tree:" << std::endl;
    BinaryTree binary_tree = BinaryTree(stack_token_list);
    std::cout << binary_tree << std::endl;
    binary_tree.printout_all();
    ConstantFolding constant_folding = ConstantFolding();
    constant_folding.calculate(binary_tree.get_root());
    binary_tree.printout_all();
    return 0;
}