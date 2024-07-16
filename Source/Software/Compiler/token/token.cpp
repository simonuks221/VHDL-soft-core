#include "token.hpp"

Token::Token(std::string _str) : str(_str) {

};

IToken *Token::clone(void) {
    return new Token(*this);
}

eToken Token::get_type(void) const {
    return eToken::Invalid;
}

std::string_view Token::get_str() const {
    return str;
}

std::string_view Token::assemble_instruction(void) const {
    return str;
}

IToken *Variable::clone()  {
    return new Variable(*this);
}

eToken Variable::get_type(void) const {
    return eToken::Variable;
}

std::string_view Variable::assemble_instruction(void) const {
    instruction = std::string("LOAD " + std::string(get_str()));
    return instruction;
}

IToken *Constant::clone()  {
    return new Constant(*this);
}

eToken Constant::get_type(void) const {
    return eToken::Constant;
}

std::string_view Constant::assemble_instruction(void) const {
    instruction = std::string("PUSH " + std::string(get_str()));
    return instruction;
}