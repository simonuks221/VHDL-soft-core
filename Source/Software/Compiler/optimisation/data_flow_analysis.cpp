#include "data_flow_analysis.hpp"
#include <algorithm>
#include <iterator>

auto find_operator_equals = [](IToken* token) {
    return (token->get_type() == eToken::Operator) && (token->get_str() == "=");
};

void DataFlowAnalysis::analyze(std::span<std::vector<IToken*>> all_tokens) {
    for(std::span<IToken*> token_line : all_tokens) {
        CFGBlock new_block;
        //TODO: a better way to do this
        if(std::find_if(token_line.begin(), token_line.end(), find_operator_equals) != token_line.end()) {
            /* Is an assignment line */
            new_block.out.insert(token_line[0]); /* Assigned variable will always be first in line */
            for(auto  it = std::next(token_line.begin()); it != token_line.end(); ++it) {
                IToken* token = *it;
                if(token->get_type() == eToken::Variable) {
                    new_block.in.insert(token);
                }
            }
        }
        blocks.push_back(new_block);
    }
}