#include <string>
#include <string_view>
#include <iostream>

#pragma once

enum class eToken {
    Invalid,
    Constant,
    Variable,
    Operator, /* For +-*^ */
    Symbol,   /* For ;{}, no instruction */
    Keyword   /* For void, int, no instruction  */
};

class IToken {
    public:
        IToken() {};
        virtual ~IToken() = default;

        virtual IToken *clone(void) const = 0;
        virtual eToken get_type(void) const = 0;

        virtual std::string_view get_str(void) const = 0;

        friend std::ostream& operator<<(std::ostream& os, const IToken& IToken) {
            os << IToken.get_str();
            return os;
        }
};

class ITokenAssemblable {
    public:
        virtual std::string_view assemble_instruction(void) const = 0;
};

/* Token that is predefined and not user created (void, int, +, *) */
class ITokenPredefined {
    public:
        ITokenPredefined();
};

class Token : public IToken {
    private:
        std::string str;
    public:
        Token(std::string _str) : str(_str) {};
        ~Token() override = default;

        IToken *clone(void) const override;
        eToken get_type(void) const override;

        std::string_view get_str(void) const override;
};

class Variable : public Token, public ITokenAssemblable {
    private:
        mutable std::string instruction;
    public:
        Variable(std::string _str) : Token(_str) {};
        virtual ~Variable() = default;

        IToken *clone(void) const override;
        eToken get_type(void) const override;
        std::string_view assemble_instruction(void) const override;
};

class Constant : public Token, public ITokenAssemblable {
    private:
        mutable std::string instruction;
    public:
        Constant(std::string _str) : Token(_str) {}; //TODO: token to int
        virtual ~Constant() = default;

        IToken *clone(void) const override;
        eToken get_type(void) const override;
        std::string_view assemble_instruction(void) const override;
};

class Keyword : public Token {
    private:
        mutable std::string instruction;
    public:
        Keyword(std::string _str);
        virtual ~Keyword() = default;

        IToken *clone(void) const override;
        eToken get_type(void) const override;
};

