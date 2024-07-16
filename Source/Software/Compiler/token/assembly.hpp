#include "line.hpp"
#include <span>
#include <vector>

#pragma once

class Assembly {
    private:
    public:
        Assembly() {};
        ~Assembly() = default;
        void assemble(std::span<ILine *> all_lines);
};