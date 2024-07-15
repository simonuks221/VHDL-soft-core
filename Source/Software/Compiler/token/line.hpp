#include "token.hpp"
#include <vector>

#pragma once

class ILine {
    private:

    public:
        ILine() {};
        virtual ~ILine() = default;
        virtual std::vector<IToken *> &get_tokens(void) = 0;

};

class Line : public ILine{
    private:
        std::vector<IToken *> tokens;
    public:
        Line() : ILine() {};
        ~Line() override = default;
        std::vector<IToken *> &get_tokens(void) override;
};