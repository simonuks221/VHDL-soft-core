#include "IOperator.hpp"

IToken *IOperator::clone() {
    return nullptr; //TODO: fix
}

unsigned int IOperator::get_presedence() const {
    return presedence;
}

bool IOperator::get_left_associative() const {
    return left_associative;
}

eToken IOperator::get_type(void) {
    return eToken::Operator;
}