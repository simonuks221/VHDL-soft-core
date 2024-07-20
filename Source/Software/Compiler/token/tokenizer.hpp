#include "token.hpp"
#include "operators.hpp"
#include "line.hpp"
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string_view>

#pragma once

class Tokenizer {
    private:
        Tokenizer() = default;
        ~Tokenizer() = default;

        static std::unordered_map<std::string, IOperator*> operators;

        static eLine classify(std::vector<IToken *> &tokens);
        static void try_parse_token(std::string &token, std::vector<IToken*> &tokens); //TODO: string view
    public:
        static bool tokenize(std::ifstream &input_stream, std::vector<ILine *> &lines);
        static bool process_tokens(std::vector<ILine *> &lines);
        static void add_operator(IToken* token);
};
