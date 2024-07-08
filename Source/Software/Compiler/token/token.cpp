#include "token.hpp"

IToken *Token::clone(void) {
    return new Token(*this);
}

eToken Token::get_type(void) {
    return eToken::Invalid;
}

std::string_view Token::get_str() const {
    return str;
}

IToken *Variable::clone()  {
    return new Variable(*this);
}

eToken Variable::get_type(void) {
    return eToken::Variable;
}

IToken *Constant::clone()  {
    return new Constant(*this);
}

eToken Constant::get_type(void) {
    return eToken::Constant;
}