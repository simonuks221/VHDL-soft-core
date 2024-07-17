#include "token.hpp"
#include "operators.hpp"
#include "line.hpp"
#include <vector>
#include <fstream>
#include <unordered_map>

#pragma once

class Tokenizer {
    private:
        Tokenizer() = default;
        ~Tokenizer() = default;

        static std::unordered_map<std::string, IOperator*> operators;

        static eLine classify(std::vector<IToken *> &tokens);
    public:
        static bool tokenize(std::ifstream &input_stream, std::vector<ILine *> &lines);
        static void add_operator(IToken* token);
};
