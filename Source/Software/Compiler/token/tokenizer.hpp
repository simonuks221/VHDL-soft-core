#include "token.hpp"
#include "operators.hpp"
#include "line.hpp"
#include <vector>
#include <fstream>
#include <unordered_map>

class Tokenizer {
    private:
        static std::unordered_map<std::string, IOperator*> operators;

        static eLine classify(std::vector<IToken *> &tokens);
    public:
        Tokenizer() {};
        ~Tokenizer() = default;

        static bool tokenize(std::ifstream &input_stream, std::vector<ILine *> &lines);
        static void add_operator(IToken* token);
};
