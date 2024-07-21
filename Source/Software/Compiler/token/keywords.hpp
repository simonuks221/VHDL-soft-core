#include "token.hpp"
#include <span>

#pragma one

class CurlyBracesKeyword : public Keyword, public ITokenAssemblable {
    private:
        mutable std::string instruction;
        bool open = false;
        unsigned int brace_idx = 0;
        CurlyBracesKeyword *other = nullptr;
    public:
        CurlyBracesKeyword(std::string _str);
        virtual ~CurlyBracesKeyword() = default;

        IToken *clone(void) const override;
        std::string_view assemble_instruction(void) const override;

        bool get_open(void) const;
        unsigned int get_brace_idx(void) const;
        void set_brace_idx(unsigned int new_value);
        void set_other(CurlyBracesKeyword *_other);
        CurlyBracesKeyword *get_other(void) const;
};

class ConditionalKeyword : public Keyword, public ITokenAssemblable, public ITokenScopeTransition {
    private:
        mutable std::string instruction;
        CurlyBracesKeyword *start_brace;
        bool should_repeat;
    public:
        ConditionalKeyword(std::string _str, bool _should_repeat) : Keyword(_str, 2, 1, false), should_repeat(_should_repeat), start_brace(nullptr) {};
        virtual ~ConditionalKeyword() = default;

        IToken *clone(void) const override;
        std::string_view assemble_instruction(void) const override;
        void shunting_yard_action(std::stack<IToken*> &operator_stack, std::vector<IToken*> &output, IToken *current) const override;

        bool parse_for_brace(std::span<IToken *> tokens) override;
        CurlyBracesKeyword *get_start_barce(void) const override;
        bool get_should_repeat(void) const override;
};

class GotoKeyword : public Keyword, public ITokenAssemblable {
    private:
        mutable std::string instruction;
        CurlyBracesKeyword *destination = nullptr;
    public:
        GotoKeyword(void) : Keyword("GOTO", 0, 1, false) {};
        virtual ~GotoKeyword() = default;

        IToken *clone(void) const override;
        std::string_view assemble_instruction(void) const override;
        void set_destination(CurlyBracesKeyword *_destination);
};