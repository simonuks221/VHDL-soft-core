#include "token.hpp"
#include "operators.hpp"
#include <vector>
#include <fstream>
#include <unordered_map>

class Tokenizer {
    private:
        std::vector<IToken*> token_list;
        std::unordered_map<std::string, IOperator*> operators;
    public:
        Tokenizer() {};
        ~Tokenizer() = default;

        std::vector<IToken*> & get_token_list(void);
        bool tokenize(std::ifstream &input_stream);
        void add_operator(IToken* token);
};
