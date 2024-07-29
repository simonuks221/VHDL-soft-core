#include <string>
#include <string_view>
#include <iostream>
#include <stack>
#include <vector>
#include <span>

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
        virtual unsigned int get_input_amount(void) const = 0;

        virtual unsigned int get_presedence(void) const = 0;
        virtual bool get_left_associative(void) const = 0;
        virtual void shunting_yard_action(std::stack<IToken*> &operator_stack, std::vector<IToken*> &output, IToken *current) const = 0;

        friend std::ostream& operator<<(std::ostream& os, const IToken& IToken) {
            os << IToken.get_str();
            return os;
        }

        friend std::ostream& operator<<(std::ostream& os, const std::vector<IToken *>& tokens) {
            for(const IToken *token : tokens) {
                os << *token << " ";
            }
            return os;
        }
};

/* Token that can be converted to assembly instruction */
class ITokenAssemblable {
    public:
        virtual std::string_view assemble_instruction(void) const = 0;
};

/* Token that is predefined and not user created (void, int, +, *) */
class ITokenPredefined {
    public:
        ITokenPredefined();
};

/* Token that trajsitions between scopes ({}) (while, if, function...) */

class CurlyBracesKeyword;

class ITokenScopeTransition {
    public:
        virtual CurlyBracesKeyword *get_start_barce(void) const = 0;
        virtual bool parse_for_brace(std::span<IToken *> tokens) = 0;
        virtual bool get_should_repeat(void) const = 0;
};

class Token : public IToken {
    private:
        std::string str;
        unsigned int input_amount;
        unsigned int presedence;
        bool left_associative;
    public:
        Token(std::string _str, unsigned int _input_amount, unsigned int _presedence, bool _left_associative) : str(_str), input_amount(_input_amount), presedence(_presedence), left_associative(_left_associative) {};
        ~Token() override = default;

        IToken *clone(void) const override;
        eToken get_type(void) const override;
        unsigned int get_input_amount(void) const override;
        virtual unsigned int get_presedence(void) const override;
        virtual bool get_left_associative(void) const override;
        virtual void shunting_yard_action(std::stack<IToken*> &operator_stack, std::vector<IToken*> &output, IToken *current) const override;

        std::string_view get_str(void) const override;
};

class Variable : public Token, public ITokenAssemblable {
    private:
        mutable std::string instruction;
        bool is_pointer = false;
        unsigned int ram_location = 0;
    public:
        Variable(std::string _str) : Token(_str, 0, 0, false) {};
        virtual ~Variable() = default;

        IToken *clone(void) const override;
        eToken get_type(void) const override;
        bool get_is_pointer(void) const;
        void set_is_pointer(bool new_value);
        void set_ram_location(unsigned int new_ram_location);
        unsigned int get_ram_location(void);
        std::string_view assemble_instruction(void) const override;
};

class Constant : public Token, public ITokenAssemblable {
    private:
        mutable std::string instruction;
    public:
        Constant(std::string _str) : Token(_str, 0, 0, false) {}; //TODO: token to int
        virtual ~Constant() = default;

        IToken *clone(void) const override;
        eToken get_type(void) const override;
        std::string_view assemble_instruction(void) const override;
};

class Keyword : public Token, public ITokenPredefined {
    private:
        mutable std::string instruction;
    public:
        Keyword(std::string _str, unsigned int _input_amount, unsigned int _presedence, bool _left_alignment) : Token(_str, _input_amount, _presedence, _left_alignment) {};
        virtual ~Keyword() = default;

        IToken *clone(void) const override;
        eToken get_type(void) const override;
};

