#include "token.hpp"
#include <vector>

#pragma once

enum class eLine {
    Default,
    Assignation,
};

class ILine {
    private:

    public:
        ILine() {};
        virtual ~ILine() = default;

        virtual std::vector<IToken *> &get_tokens(void) = 0;
        virtual std::vector<IToken *> &get_variables_in(void) = 0;
        virtual std::vector<IToken *> &get_variables_out(void) = 0;
        virtual eLine get_type(void) = 0;
};

class Line : public ILine {
    private:
        std::vector<IToken *> tokens;
    protected:
        std::vector<IToken *> tokens_in;
        std::vector<IToken *> tokens_out;
    public:
        Line(std::vector<IToken *> &_tokens) : tokens(_tokens) {}; //TODO: do not copy token vector
        ~Line() override = default;
        std::vector<IToken *> &get_tokens(void) override;
        std::vector<IToken *> &get_variables_in(void) override;
        std::vector<IToken *> &get_variables_out(void) override;
        eLine get_type(void) override;
};

class LineAssignation : public Line {
    private:

    public:
        LineAssignation(std::vector<IToken *> &_tokens);
        ~LineAssignation() override = default;
        eLine get_type(void) override;
};