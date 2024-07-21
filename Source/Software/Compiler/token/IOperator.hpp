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

class IOperator : public Token, public ITokenAssemblable, public ITokenPredefined {
    public:
        IOperator(std::string _str, unsigned int _input_amount, unsigned int _presedence, bool _left_associative) : Token(_str, _input_amount, _presedence, _left_associative), ITokenPredefined() {};
        virtual ~IOperator() = default;

        virtual uint8_t get_properties(void) const = 0;
        virtual bool has_property(eOperatorProperty) const = 0;
};