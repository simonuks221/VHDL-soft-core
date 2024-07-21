#include "tokenizer.hpp"
#include "keywords.hpp"

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
// BaseOperator open_braces("{", 0, true, "{"); //TODO: now hardcoded in
// BaseOperator closed_braces("}", 0, true, "}");
CurlyBracesKeyword open_braces("{");
CurlyBracesKeyword closed_braces("}");
// Keyword if_cond("if");
// Keyword true_cond("true");
// Keyword false_cond("false");
ConditionalKeyword while_cond("while", true);
ConditionalKeyword for_cond("for", true); //TODO: for examplory purpose only
ConditionalKeyword if_cond("if", false);

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
            // if((ch == '{') || (ch == '}')) {
            //     /* Found braces keyword */ //TODO: no hardcode
            //     Keyword *new_token = new Keyword(std::string(1, ch));
            //     temp_tokens.push_back(new_token);
            //     continue;
            // }
            if(isdigit(ch) || isalnum(ch)) {
                temp_token += ch;
                continue;
            }
            try_parse_token(temp_token, temp_tokens);
            std::string ch_str(1, ch);
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

bool Tokenizer::process_tokens(std::vector<ILine *> &lines) {
    /* Find all braces and index them */
    std::stack<std::pair<unsigned int, CurlyBracesKeyword *>> brace_indexes;
    unsigned int max_braces_index = 1;
    for(ILine *line : lines) {
        for(IToken *token : line->get_tokens()) {
            if(token->get_type() != eToken::Keyword) {
                continue;
            }
            CurlyBracesKeyword *keyword = dynamic_cast<CurlyBracesKeyword *>(token);
            if(keyword == nullptr) {
                continue;
            }
            if(keyword->get_open()) {
                keyword->set_brace_idx(max_braces_index);
                brace_indexes.push(std::make_pair(max_braces_index, keyword));
                max_braces_index++;
            } else {
                if(brace_indexes.empty()) {
                    std::cerr << "Invalid braces" << std::endl;
                    assert(false);
                }
                keyword->set_brace_idx(brace_indexes.top().first);
                keyword->set_other(brace_indexes.top().second);
                brace_indexes.top().second->set_other(keyword);
                brace_indexes.pop();
            }
        }
    }
    if(!brace_indexes.empty()) {
        std::cerr << "Invalid braces at the end" << std::endl;
        assert(false);
    }
    /* Find all block transition keywords */
    for(ILine *line : lines) {
        for(IToken *token : line->get_tokens()) {
            if(token->get_type() != eToken::Keyword) {
                continue;
            }
            ITokenScopeTransition *transition = dynamic_cast<ITokenScopeTransition *>(token);
            if(transition == nullptr) {
                continue;
            }
            if(!transition->parse_for_brace(line->get_tokens())) {
                std::cerr << "Failed to parse for while braces " << std::endl;
                assert(false);
                return false;
            }
            /* Insert start brace at the start of the line - so the jump tp it would envelop argument loading */
            CurlyBracesKeyword *start_brace = transition->get_start_barce();
            auto it = std::find(line->get_tokens().begin(), line->get_tokens().end(), start_brace);
            if(it == line->get_tokens().end()) {
                std::cerr << "Failed to refind brace in line" << std::endl;
                assert(false);
            }
            line->get_tokens().erase(it);
            line->get_tokens().insert( line->get_tokens().begin(), start_brace);

            if(transition->get_should_repeat()) {
                /* Add return to while at block end - search for the lines of block end brace */
                IToken *brace_to_find = transition->get_start_barce()->get_other();
                for(ILine *find_line : lines) {
                    auto it = std::find(find_line->get_tokens().begin(), find_line->get_tokens().end(), brace_to_find);
                    if(it == find_line->get_tokens().end()) {
                        continue;
                    }
                    /* Make goto at the end of block to point to start condition */
                    GotoKeyword *goto_keyword = new GotoKeyword();
                    goto_keyword->set_destination(transition->get_start_barce());
                    find_line->get_tokens().insert(it, goto_keyword);
                    break;
                } //TODO: clean up into functions
            }

            break; //TODO: will not work with 2 whiles in one line
        }
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
