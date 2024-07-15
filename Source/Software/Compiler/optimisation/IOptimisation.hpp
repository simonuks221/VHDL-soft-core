#include "token/line.hpp"

#pragma once

class IOptimisation {
    public:
        IOptimisation() {};
        virtual ~IOptimisation() = default;
        virtual void calculate(std::vector<ILine *> &all_lines) = 0;
};