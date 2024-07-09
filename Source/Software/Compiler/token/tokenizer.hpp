#include "token.hpp"
#include <vector>
#include <fstream>

class Tokenizer {
    private:
        std::vector<IToken*> token_list;
    public:
        Tokenizer() {};
        ~Tokenizer() = default;

        std::vector<IToken*> & get_token_list(void);
        bool tokenize(std::ifstream &input_stream);
};