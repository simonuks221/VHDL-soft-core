#include <string>
#include <string_view>
#include <iostream>

#pragma once

class Token {
    private:
        std::string str;
    public:
        Token(std::string _str) : str(_str) {};
        virtual ~Token() = default;

        virtual Token *clone(void) { return nullptr;} ; //TODO: make into virtual class

        std::string_view get_str(void) const;
};

class Variable : public Token {
    public:
        Variable(std::string _str) : Token(_str) {};
        virtual ~Variable() = default;

        Token *clone() override;
};

class Constant : public Token {
    public:
        Constant(std::string _str) : Token(_str) {}; //TODO: token to int
        virtual ~Constant() = default;

        Token *clone() override;
};

