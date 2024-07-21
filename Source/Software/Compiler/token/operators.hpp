#include "IOperator.hpp"
#include <string_view>
#include <string>

#pragma once

class BaseOperator : public IOperator {
    private:
        const uint8_t properties;
        std::string asm_instruction;
    public:
        BaseOperator(std::string _str, unsigned int _presedence, bool _left, std::string _asm_instruction, uint8_t _properties) : IOperator(_str, 2, _presedence, _left), asm_instruction(_asm_instruction), properties(_properties) {};
        BaseOperator(std::string _str, unsigned int _presedence, bool _left, std::string _asm_instruction) : IOperator(_str, 2, _presedence, _left), asm_instruction(_asm_instruction), properties(0) {};
        BaseOperator(std::string _str, unsigned int _presedence, bool _left) : IOperator(_str, 2, _presedence, _left), asm_instruction(""), properties(0) {};
        virtual ~BaseOperator() = default;

        IToken *clone(void) const override;
        eToken get_type(void) const override;
        uint8_t get_properties(void) const override;
        bool has_property(eOperatorProperty) const override;
        void shunting_yard_action(std::stack<IToken*> &operator_stack, std::vector<IToken*> &output, IToken *current) const override;
        std::string_view assemble_instruction(void) const override;
};

class IgnoreOperator : public BaseOperator {
    public:
        IgnoreOperator(std::string _str) : BaseOperator(_str, 0, true) { };
        virtual ~IgnoreOperator() = default;
        IToken *clone(void) const override;

        void shunting_yard_action(std::stack<IToken*> &operator_stack, std::vector<IToken*> &output, IToken *current) const override;
};

class FunctionOperator : public BaseOperator {
    public:
        FunctionOperator(std::string _str, std::string _asm) : BaseOperator(_str, 0, true, _asm) {};
        virtual ~FunctionOperator() = default;
        IToken *clone(void) const override;

        void shunting_yard_action(std::stack<IToken*> &operator_stack, std::vector<IToken*> &output, IToken *current) const override;
        std::string_view assemble_instruction(void) const override;
};

class ParentehsiesOperator : public BaseOperator {
    public:
        ParentehsiesOperator(std::string _str) : BaseOperator(_str, 0, true) {};
        virtual ~ParentehsiesOperator() = default;
        IToken *clone(void) const override;

        void shunting_yard_action(std::stack<IToken*> &operator_stack, std::vector<IToken*> &output, IToken *current) const override;
};
