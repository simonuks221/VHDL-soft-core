#include "token.hpp"
#include "operators.hpp"
#include "line.hpp"
#include <vector>
#include <fstream>
#include <unordered_map>

class Tokenizer {
    private:
        std::unordered_map<std::string, IOperator*> operators;
    public:
        Tokenizer() {};
        ~Tokenizer() = default;

        bool tokenize(std::ifstream &input_stream, std::vector<ILine *> &lines);
        void add_operator(IToken* token);
};
