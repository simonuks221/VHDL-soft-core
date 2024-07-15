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
#include "token/assembly.hpp"
#include "token/tokenizer_singleton.hpp"
#include "token/line.hpp"
#include "binary_tree/binary_tree.hpp"
#include "optimisation/constant_folding.hpp"
#include "optimisation/data_flow_analysis.hpp"

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
    /* Open file specified from input arguments */
    std::string file_path;
    if(argc != 2) {
        std::cerr << "Invalid amount of arguments" << std::endl;
        /* Use deafult path */
        file_path = "../code.txt";
    } else {
        file_path = argv[1];
    }
    /* Check if file correctly opened */
    std::ifstream inputFile(file_path);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file: " << file_path << std::endl;
        return 1;
    }
    /* Tokenize */
    std::vector<ILine *> lines;
    TokenizerSingleton::get_instance().tokenize(inputFile, lines);
    inputFile.close();
    std::cout << "Got tokens:" <<std::endl;
    for(ILine * line : lines) {
        for(IToken *token : line->get_tokens()) {
            std::cout << *token << " ";
        }
        std::cout << std::endl;
    }

    // /* Do shunting yard to convert sequentially */
    // std::vector<std::vector<IToken*>> stack_token_list;
    // for(std::vector<IToken*> token_line : tokenizer.get_token_list()) {
    //     std::vector<IToken*> temp_stack_token_list;
    //     convert_to_stack_ops(token_line, temp_stack_token_list);
    //     stack_token_list.push_back(temp_stack_token_list);
    // }

    // std::cout << "Got stack ops:" <<std::endl;
    // for(std::vector<IToken*> token_line : stack_token_list) {
    //     for(IToken *token : token_line) {
    //         std::cout << *token << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // /* Convert to binary trees */
    // std::vector<BinaryTree> binary_trees;
    // std::cout << "Got binary tree:" << std::endl;
    // for(std::vector<IToken*> token_line : stack_token_list) {
    //     BinaryTree temp_binary_tree = BinaryTree(token_line);
    //     binary_trees.push_back(temp_binary_tree);
    //     std::cout << temp_binary_tree << std::endl;
    // }
    // /* Do constant folding */
    // std::cout << "Constant folding: " << std::endl;
    // ConstantFolding constant_folding = ConstantFolding();
    // for(BinaryTree binary_tree : binary_trees) {
    //     constant_folding.calculate(binary_tree.get_root());
    //     std::cout << binary_tree << std::endl;
    // }
    /* Do data flow analysis */
    // DataFlowAnalysis data_flow_analysis;
    // data_flow_analysis.analyze(stack_token_list);
    // /* Assemble, convert into instructions */
    // Assembly assembly;
    // assembly.assemble(stack_token_list);
    return 0;
}