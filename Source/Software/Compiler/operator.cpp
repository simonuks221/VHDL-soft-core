#include "operator.hpp"

std::string_view Operator::get_str() const {
    return str;
}

unsigned int Operator::get_presedence() const {
    return presedence;
}

bool Operator::get_left_associative() const {
    return left_associative;
}