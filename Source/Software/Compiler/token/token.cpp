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

//TODO: does not work
// std::ostream& operator<<(std::ostream& os, const Token& obj) {
//     std::string str(obj.get_str());
//     return os << str;
// }

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