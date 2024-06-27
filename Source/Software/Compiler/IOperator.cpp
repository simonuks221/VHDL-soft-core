#include "IOperator.hpp"

unsigned int IOperator::get_presedence() const {
    return presedence;
}

bool IOperator::get_left_associative() const {
    return left_associative;
}