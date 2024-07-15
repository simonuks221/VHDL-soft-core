#include "tokenizer.hpp"

#include <unordered_set>
#include <algorithm>
#include <cassert>

//TODO: nicer associative setting
BaseOperator addition("+", 2, true, "ADD", static_cast<uint8_t>(static_cast<uint8_t>(eOperatorProperty::Associative) | static_cast<uint8_t>(eOperatorProperty::Commutative)));
BaseOperator subtraction("-", 2, true, "SUB");
BaseOperator multiplication("*", 3, true, "MULT", static_cast<uint8_t>(static_cast<uint8_t>(eOperatorProperty::Associative) | static_cast<uint8_t>(eOperatorProperty::Commutative)));
BaseOperator division("/", 3, true, "DIV");
BaseOperator power("^", 4, false, "PWR");
ParentehsiesOperator closing_parentheses(")");
ParentehsiesOperator opening_parentheses("(");
FunctionOperator sin_func("sin", "SINE"); //TODO: wont have these sinthesisable
FunctionOperator max_func("max", "MAX");
IgnoreOperator comma(",");
BaseOperator assign("=", 0, true, "ASSGN"); //TODO: should not synthesize

void Tokenizer::add_operator(IToken* token) {
    IOperator *op = static_cast<IOperator *>(token);
    assert(op != nullptr);
    operators.insert_or_assign(op->get_str().data(), op); //TODO: map with string_views?
}

bool Tokenizer::tokenize(std::ifstream &input_stream, std::vector<ILine *> &lines) {
    std::string temp_token = "";
    std::string file_line;
    while (std::getline(input_stream, file_line)) {
        temp_token.clear();
        std::vector<IToken*> temp_tokens;
        for (char ch : file_line) {
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
        /* End of line, add to lines container */
        if(temp_tokens.empty()) {
            continue;
        }
        //TODO: make line factory
        ILine *new_line = nullptr;
        /* First classify what line got */
        switch(classify(temp_tokens)) {
            case eLine::Default : {
                new_line = new Line(temp_tokens);
            } break;
            case eLine::Assignation : {
                new_line = new LineAssignation(temp_tokens);
            }break;
        }

        lines.push_back(new_line);
    }
    return true;
}

static auto find_line_equals = [](IToken* token) {
    return token->get_str() == "=";
};

eLine Tokenizer::classify(std::vector<IToken *> &tokens) {
    if(std::find_if(tokens.begin(), tokens.end(), find_line_equals) != tokens.end()) {
        /* Is an assignment line */
        return eLine::Assignation;
    }
    return eLine::Default;
}
