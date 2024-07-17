#include "line.hpp"
#include <span>
#include <vector>

#pragma once

class Assembly {
    private:
    public:
        Assembly() {};
        ~Assembly() = default;
        static void assemble(std::span<ILine *> all_lines);
};