#include <string>
#include <string_view>
#include <iostream>

#pragma once

enum class eToken {
    Invalid,
    Constant,
    Variable,
    Operator
};

class IToken {
    public:
        IToken() {};
        virtual ~IToken() = default;

        virtual IToken *clone(void) = 0;
        virtual eToken get_type(void) = 0;

        virtual std::string_view get_str(void) const = 0;

        friend std::ostream& operator<<(std::ostream& os, const IToken& IToken) {
            os << IToken.get_str();
            return os;
        }
};

class Token : public IToken{
    private:
        std::string str;
    public:
        Token(std::string _str) : str(_str) {};
        ~Token() override = default;

        IToken *clone(void) override;
        eToken get_type(void) override;

        std::string_view get_str(void) const override;
};

class Variable : public Token {
    public:
        Variable(std::string _str) : Token(_str) {};
        virtual ~Variable() = default;

        IToken *clone() override;
        eToken get_type(void) override;
};

class Constant : public Token {
    public:
        Constant(std::string _str) : Token(_str) {}; //TODO: token to int
        virtual ~Constant() = default;

        IToken *clone() override;
        eToken get_type(void) override;
};

