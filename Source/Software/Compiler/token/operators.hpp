#include "IOperator.hpp"
#include <string_view>
#include <string>

#pragma once

class BaseOperator : public IOperator {
    private:
        unsigned int presedence;
        bool left_associative;
        const uint8_t properties;
        std::string asm_instruction;
    public:
        BaseOperator(std::string _str, unsigned int _presedence, bool _left, std::string _asm_instruction, uint8_t _properties);
        BaseOperator(std::string _str, unsigned int _presedence, bool _left, std::string _asm_instruction);
        BaseOperator(std::string _str, unsigned int _presedence, bool _left);
        virtual ~BaseOperator() = default;

        IToken *clone(void) override;
        eToken get_type(void) override;
        unsigned int get_presedence(void) const override;
        bool get_left_associative(void) const override;
        uint8_t get_properties(void) const override;
        bool has_property(eOperatorProperty) const override;
        void shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<IToken*> &output) const override;
        std::string_view assemble_instruction(void) override;
};

class IgnoreOperator : public BaseOperator {
    public:
        IgnoreOperator(std::string _str) : BaseOperator(_str, 0, true) { };
        virtual ~IgnoreOperator() = default;
        IToken *clone(void) override;

        void shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<IToken*> &output) const override;
};

class FunctionOperator : public BaseOperator {
    public:
        FunctionOperator(std::string _str, std::string _asm) : BaseOperator(_str, 0, true, _asm) {};
        virtual ~FunctionOperator() = default;
        IToken *clone(void) override;

        void shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<IToken*> &output) const override;
        std::string_view assemble_instruction(void) override;
};

class ParentehsiesOperator : public BaseOperator {
    public:
        ParentehsiesOperator(std::string _str) : BaseOperator(_str, 0, true) {};
        virtual ~ParentehsiesOperator() = default;
        IToken *clone(void) override;

        void shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<IToken*> &output) const override;
};
