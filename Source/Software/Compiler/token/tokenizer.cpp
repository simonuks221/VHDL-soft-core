#include "tokenizer.hpp"
#include "operators.hpp"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

static const std::unordered_map<std::string, IOperator*> operators = { //TODO: make property assignment nicer
    {"+", new BaseOperator("+", 2, true, static_cast<uint8_t>(static_cast<uint8_t>(eOperatorProperty::Associative) | static_cast<uint8_t>(eOperatorProperty::Commutative)))},
    {"-", new BaseOperator("-", 2, true)},
    {"*", new BaseOperator("*", 3, true, static_cast<uint8_t>(static_cast<uint8_t>(eOperatorProperty::Associative) | static_cast<uint8_t>(eOperatorProperty::Commutative)))},
    {"/", new BaseOperator("/", 3, true)},
    {"^", new BaseOperator("^", 4, false)}, {"(", new ParentehsiesOperator("(")},
    {")", new ParentehsiesOperator(")")}, {"sin", new FunctionOperator("sin")},
    {"max", new FunctionOperator("max")}, {",", new IgnoreOperator(",")}};


bool Tokenizer::tokenize(std::ifstream &input_stream) {
    std::string temp_token = "";
    std::string line;
    while (std::getline(input_stream, line)) {
        temp_token.clear();
        for (char ch : line) {
            if(ch == '#') {
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
    }
    return true;
}

std::vector<IToken*>& Tokenizer::get_token_list(void) {
    return token_list;
}