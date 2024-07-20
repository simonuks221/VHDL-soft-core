#include "token.hpp"
#include "tokenizer.hpp"
#include <cassert>

IToken *Token::clone(void) const {
    return new Token(*this);
}

eToken Token::get_type(void) const {
    return eToken::Invalid;
}

std::string_view Token::get_str() const {
    return str;
}

IToken *Variable::clone() const {
    return new Variable(*this);
}

eToken Variable::get_type(void) const {
    return eToken::Variable;
}

std::string_view Variable::assemble_instruction(void) const {
    instruction = std::string("LOAD " + std::string(get_str()));
    return instruction;
}

IToken *Constant::clone() const {
    return new Constant(*this);
}

eToken Constant::get_type(void) const {
    return eToken::Constant;
}

std::string_view Constant::assemble_instruction(void) const {
    instruction = std::string("PUSH " + std::string(get_str()));
    return instruction;
}

IToken *Keyword::clone() const {
    return new Keyword(*this);
}

eToken Keyword::get_type(void) const {
    return eToken::Keyword;
}

ITokenPredefined::ITokenPredefined() {
    IToken *token = reinterpret_cast<IToken *>(this); //TODO: figure a way to use dynamic_cast
    if(token == nullptr) {
        std::cerr << "Predefined token not in Itoken child" << std::endl;
        assert(false);
    }
    Tokenizer::add_operator(token);
}

Keyword::Keyword(std::string _str) : Token(_str) {
    Tokenizer::add_operator(this);
};
