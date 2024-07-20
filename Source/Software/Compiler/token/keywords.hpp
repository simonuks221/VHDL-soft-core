#include "token.hpp"
#include <span>

#pragma one

class CurlyBracesKeyword : public Keyword, public ITokenAssemblable {
    private:
        mutable std::string instruction;
        bool open = false;
        unsigned int brace_idx = 0;
    public:
        CurlyBracesKeyword(std::string _str);
        virtual ~CurlyBracesKeyword() = default;

        IToken *clone(void) const override;
        std::string_view assemble_instruction(void) const override;

        bool get_open(void) const;
        unsigned int get_brace_idx(void) const;
        void set_brace_idx(unsigned int new_value);
};

class WhileKeyword : public Keyword, public ITokenAssemblable {
    private:
        mutable std::string instruction;
        unsigned int brace_idx = 0;
    public:
        WhileKeyword(std::string _str) : Keyword(_str) {};
        virtual ~WhileKeyword() = default;

        IToken *clone(void) const override;
        std::string_view assemble_instruction(void) const override;

        unsigned int get_brace_idx(void) const;
        void set_brace_idx(unsigned int new_value);
        bool parse_for_brace(std::span<IToken *> tokens);
};