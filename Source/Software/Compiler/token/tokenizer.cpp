#include "tokenizer.hpp"

#include <unordered_set>
#include <algorithm>
#include <cassert>

//TODO: nicer associative setting
BaseOperator addition("+", 2, true, static_cast<uint8_t>(static_cast<uint8_t>(eOperatorProperty::Associative) | static_cast<uint8_t>(eOperatorProperty::Commutative)));
BaseOperator subtraction("-", 2, true);
BaseOperator multiplication("*", 3, true, static_cast<uint8_t>(static_cast<uint8_t>(eOperatorProperty::Associative) | static_cast<uint8_t>(eOperatorProperty::Commutative)));
BaseOperator division("/", 3, true);
BaseOperator power("^", 4, false);
ParentehsiesOperator closing_parentheses(")");
ParentehsiesOperator opening_parentheses("(");
FunctionOperator sin_func("sin");
FunctionOperator max_func("max");
IgnoreOperator comma(",");
BaseOperator assign("=", 0, true);


void Tokenizer::add_operator(IToken* token) {
    IOperator *op = static_cast<IOperator *>(token);
    assert(op != nullptr);
    operators.insert_or_assign(op->get_str().data(), op); //TODO: map with string_views?
}

bool Tokenizer::tokenize(std::ifstream &input_stream) {
    std::string temp_token = "";
    std::string line;
    while (std::getline(input_stream, line)) {
        temp_token.clear();
        std::vector<IToken*> temp_tokens;
        for (char ch : line) {
            if((ch == '#') || (ch == ';')) { //TODO: will skip everything in a line after ;
                /* Found start of comment */
                break;
            }
            if(isdigit(ch) || isalnum(ch)) {
                temp_token += ch;
                continue;
            }
            std::string ch_str(1, ch);
            if(!temp_token.empty()) {
                if(operators.find(temp_token) != operators.end()) {
                    /* Operator in temp_token */
                    IToken *new_token = operators.at(temp_token)->clone();
                    temp_tokens.push_back(new_token);
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
                    temp_tokens.push_back(new_token);
                    temp_token.clear();
                }
            }
            if(operators.find(ch_str) != operators.end()) {
                /* found operator */
                IToken *new_token = operators.at(ch_str)->clone();
                temp_tokens.push_back(new_token);
                temp_token.clear();
            }
        }
        if(!temp_token.empty()) {
            //TODO: duplicated code
            if(operators.find(temp_token) != operators.end()) {
                /* Operator in temp_token */
                IToken *new_token = operators.at(temp_token)->clone();
                temp_tokens.push_back(new_token);
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
                temp_tokens.push_back(new_token);
            }
        }
        if(!temp_token.empty()) {
            token_list.push_back(temp_tokens);
        }
    }
    return true;
}

std::vector<std::vector<IToken*>>& Tokenizer::get_token_list(void) {
    return token_list;
}