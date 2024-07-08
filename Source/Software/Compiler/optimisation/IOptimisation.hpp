#include "binary_tree.hpp"

#pragma once

class IOptimisation {
    public:
        IOptimisation() {};
        virtual ~IOptimisation() = default;
        virtual void calculate(TreeNode *root) = 0;
};