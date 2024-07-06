#include "IOptimisation.hpp"

class ConstantFolding : IOptimisation {
    public:
        ConstantFolding();
        ~ConstantFolding() override = default;
        void calculate(TreeNode *root) override;
};