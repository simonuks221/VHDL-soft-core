#include "token.hpp"
#include <vector>

class Tokenizer {
    private:

    public:
        Tokenizer() {};
        ~Tokenizer() = default;

        bool tokenize(std::string_view input, std::vector<IToken*> &token_list);
};