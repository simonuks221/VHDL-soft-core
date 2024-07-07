#include "token.hpp"

std::string_view Token::get_str() const {
    return str;
}

//TODO: does not work
std::ostream& operator<<(std::ostream& os, const Token& obj) {
    std::string str(obj.get_str());
    return os << str;
}

Token *Variable::clone()  {
    return new Variable(*this);
}

eToken Variable::get_type(void) {
    return eToken::Variable;
}

Token *Constant::clone()  {
    return new Constant(*this);
}

eToken Constant::get_type(void) {
    return eToken::Constant;
}