#include "IOperator.hpp"
#include <string_view>
#include <string>

#pragma once

class BaseOperator : public IOperator {
    public:
        BaseOperator(std::string _str, unsigned int _presedence, bool _left) : IOperator(_str, _presedence, _left) {};
        virtual ~BaseOperator() = default;
        IToken *clone(void) override;

        void shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<IToken*> &output) const override;
};

class IgnoreOperator : public BaseOperator {
    public:
        IgnoreOperator(std::string _str) : BaseOperator(_str, 0, true) {};
        virtual ~IgnoreOperator() = default;
        IToken *clone(void) override;

        void shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<IToken*> &output) const override;
};

class FunctionOperator : public BaseOperator {
    public:
        FunctionOperator(std::string _str) : BaseOperator(_str, 0, true) {};
        virtual ~FunctionOperator() = default;
        IToken *clone(void) override;

        void shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<IToken*> &output) const override;
};

class ParentehsiesOperator : public BaseOperator {
    public:
        ParentehsiesOperator(std::string _str) : BaseOperator(_str, 0, true) {};
        virtual ~ParentehsiesOperator() = default;
        IToken *clone(void) override;

        void shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<IToken*> &output) const override;
};
