#include "IOperator.hpp"

std::string_view IOperator::get_str() const {
    return str;
}

unsigned int IOperator::get_presedence() const {
    return presedence;
}

bool IOperator::get_left_associative() const {
    return left_associative;
}