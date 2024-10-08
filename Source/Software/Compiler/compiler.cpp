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
#include "token/tokenizer.hpp"
#include "token/line.hpp"
#include "optimisation/constant_folding.hpp"
#include "optimisation/data_flow_analysis.hpp"
#include "resolvers/cycles_resolver.hpp"
#include "resolvers/variables_resolver.hpp"
#include "logging.hpp"

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

bool convert_to_stack_ops(std::vector<IToken *> &tokens) {
    /* Shunting yard algorithm to convert tokens to stack operations */
    std::stack<IToken *> operator_stack;
    std::vector<IToken *> output;
    for (IToken *token : tokens) {
        token->shunting_yard_action(operator_stack, output, token);
    }
    /* Add all operators that are left from stack */
    while(!operator_stack.empty()) {
        output.push_back(operator_stack.top());
        operator_stack.pop();
    }
    tokens = output;
    return true;
}

int main(int argc, char* argv[]) {
    /* Open file specified from input arguments */
    std::string file_path;
    if(argc != 2) {
        Logging::error("Invalid amount of arguments");
        /* Use deafult path */
        file_path = "../code.txt";
    } else {
        file_path = argv[1];
    }
    /* Check if file correctly opened */
    std::ifstream inputFile(file_path);
    if (!inputFile.is_open()) {
        Logging::error("Failed to open the file " + file_path);
        return 1;
    }
    /* Tokenize */
    std::vector<ILine *> lines;
    Tokenizer::tokenize(inputFile, lines);
    inputFile.close();
    Tokenizer::process_tokens(lines);
    VariablesResolver::get_instance().resolve(lines);
    CyclesResolver::resolve(lines);
    Logging::info("Got tokens:");
    for(ILine *line : lines) {
        std::cout << line->get_tokens() << std::endl;
    }
    /* Do data flow analysis */
    DataFlowAnalysis data_flow_analysis; //TODO: singleton
    data_flow_analysis.analyze(lines);
    /* Do shunting yard to convert sequentially */
    Logging::info("Stack operations:");
    for(ILine *line : lines) {
        convert_to_stack_ops(line->get_tokens());
        std::cout << line->get_tokens() << std::endl;
        for(const IToken *token : line->get_tokens()) {
            std::cout << token << " ";
        }
        std::cout << std::endl;
    }
    /* Do constant folding */
    ConstantFolding::calculate(lines);
    Logging::info("Tokens left:");
    for(ILine *line : lines) {
        std::cout << line->get_tokens() << std::endl;
    }
    /* Assemble, convert into instructions */
    Assembly::assemble(lines);
    Logging::info("Success");
    return 0;
}