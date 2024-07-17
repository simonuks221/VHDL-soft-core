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
        virtual eLine get_type(void) const = 0;
        virtual void replace_token(IToken *new_token, unsigned int index) = 0;
        virtual void replace_token(IToken *old_token, IToken *new_token) = 0;
};

class Line : public ILine {
    private:

    protected:
        std::vector<IToken *> tokens;
        std::vector<IToken *> tokens_in;
        std::vector<IToken *> tokens_out;

        virtual void update_tokens_in_out(void);
    public:
        Line(std::vector<IToken *> &_tokens);
        ~Line() override = default;
        std::vector<IToken *> &get_tokens(void) override;
        std::vector<IToken *> &get_variables_in(void) override;
        std::vector<IToken *> &get_variables_out(void) override;
        eLine get_type(void) const override;
        void replace_token(IToken *new_token, unsigned int index) override;
        void replace_token(IToken *old_token, IToken *new_token) override;
};

class LineAssignation : public Line {
    private:

    protected:
        void update_tokens_in_out(void) override;

    public:
        LineAssignation(std::vector<IToken *> &_tokens);
        ~LineAssignation() override = default;
        eLine get_type(void) const override;
};