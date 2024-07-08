#include <string>
#include <cstdint>
#include <stack>
#include <vector>
#include "token.hpp"

#pragma once

/* Enum of flags */
enum class eOperatorProperty {
    Commutative = 1 << 0,
    Associative = 1 << 1,
};

class IOperator : public Token {
    public:
        IOperator(std::string _str) : Token(_str) {};
        virtual ~IOperator() = default;

        virtual unsigned int get_presedence(void) const = 0;
        virtual bool get_left_associative(void) const = 0;
        virtual uint8_t get_properties(void) const = 0;
        virtual bool has_property(eOperatorProperty) const = 0;
        //TODO: make static
        virtual void shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<IToken*> &output) const = 0;
};