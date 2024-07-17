#include "line.hpp"
#include <span>
#include <vector>

#pragma once

class Assembly {
    private:
        Assembly() = default;
        ~Assembly() = default;
    public:
        static void assemble(std::span<ILine *> all_lines);
};