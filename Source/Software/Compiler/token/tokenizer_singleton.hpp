#include "tokenizer.hpp"
#include <vector>
#include <fstream>

#pragma once

class TokenizerSingleton : Tokenizer {
    protected:
        TokenizerSingleton() {};
        ~TokenizerSingleton() = default;
    public:
        TokenizerSingleton(TokenizerSingleton &other) = delete;
        void operator=(const TokenizerSingleton &) = delete;

        static Tokenizer &get_instance(void) {
            static Tokenizer tokenizer;
            return tokenizer;
        }
};