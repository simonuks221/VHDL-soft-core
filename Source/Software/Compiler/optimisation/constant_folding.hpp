#include "line.hpp"
#include <vector>

#pragma once

class ConstantFolding {
    private:
        ConstantFolding() = default;
        ~ConstantFolding() = default;
    public:
        static void calculate(std::vector<ILine *> &all_lines);
};