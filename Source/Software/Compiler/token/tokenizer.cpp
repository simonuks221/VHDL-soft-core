#include "tokenizer.hpp"

#include <unordered_set>
#include <algorithm>
#include <cassert>

uint8_t operator|(eOperatorProperty a, eOperatorProperty b);

std::unordered_map<std::string, IOperator*> Tokenizer::operators;

static uint8_t associative_and_commutative = eOperatorProperty::Associative | eOperatorProperty::Commutative;

BaseOperator addition("+", 2, true, "ADD", associative_and_commutative);
BaseOperator subtraction("-", 2, true, "SUB");
BaseOperator multiplication("*", 3, true, "MULT", associative_and_commutative);
BaseOperator division("/", 3, true, "DIV");
BaseOperator power("^", 4, false, "PWR");
ParentehsiesOperator closed_parentheses(")");
ParentehsiesOperator open_parentheses("(");
FunctionOperator sin_func("sin", "SINE"); //TODO: won't have these sinthesisable
FunctionOperator max_func("max", "MAX");
IgnoreOperator comma(",");
BaseOperator assign("=", 0, true, "ASSGN"); //TODO: should not synthesize
BaseOperator if_cond("if", 0, true, "ASSGN");
BaseOperator true_cond("true", 0, true, "1");
BaseOperator false_cond("false", 0, true, "0");
BaseOperator open_braces("{", 0, true, "{");
BaseOperator closed_braces("}", 0, true, "}");

void Tokenizer::add_operator(IToken* token) {
    IOperator *op = static_cast<IOperator *>(token);
    assert(op != nullptr);
    operators.insert_or_assign(op->get_str().data(), op); //TODO: map with string_views?
}

void Tokenizer::try_parse_token(std::string &token, std::vector<IToken*> &tokens) {
    if(token.empty()) {
        return;
    }
    if(operators.find(token) != operators.end()) {
        /* Operator in temp_token */
        IToken *new_token = operators.at(token)->clone();
        tokens.push_back(new_token);
    } else {
        /* No operator in temp_token */
        IToken *new_token = nullptr;
        bool is_all_num = std::all_of(token.begin(), token.end(), ::isdigit);
        if(is_all_num) {
            /* All numbers - constant */
            new_token = new Constant(token);
        } else {
            /* Variable */
            new_token = new Variable(token);
        }
        tokens.push_back(new_token);
    }
    token.clear();
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
            try_parse_token(temp_token, temp_tokens);
            if(operators.find(ch_str) != operators.end()) {
                /* Found operator */
                IToken *new_token = operators.at(ch_str)->clone();
                temp_tokens.push_back(new_token);
                temp_token.clear();
            }
        }
        try_parse_token(temp_token, temp_tokens);
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

uint8_t operator|(eOperatorProperty a, eOperatorProperty b) {
    return static_cast<uint8_t>(a) + static_cast<uint8_t>(b);
}
