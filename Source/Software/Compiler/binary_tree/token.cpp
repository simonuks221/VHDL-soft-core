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

Token *Constant::clone()  {
    return new Constant(*this);
}