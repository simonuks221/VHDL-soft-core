#include "IOptimisation.hpp"

#pragma once

class ConstantFolding : IOptimisation {
    public:
        ConstantFolding();
        ~ConstantFolding() override = default;
        void calculate(TreeNode *root) override;
};