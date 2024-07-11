#include "token.hpp"
#include <span>
#include <vector>

#pragma once

class Assembly {
    private:
    public:
        Assembly() {};
        ~Assembly() = default;
        void assemble(std::span<std::vector<IToken*>> all_tokens);
};