#include "constant_folding.hpp"

ConstantFolding::ConstantFolding() {

}

static int calculate_node(TreeNode* node) { //TODO: namespace
    if (node == nullptr) {
        return 0;
    }
    /* Check if operator */
    IOperator *op = dynamic_cast<IOperator*>(node->token);
    if(op != nullptr) {
        if((op->get_str() == "+") || (op->get_str() == "*")) { //TODO: remove hardcode
            Constant *op_left = dynamic_cast<Constant*>(node->left->token);
            Constant *op_right = dynamic_cast<Constant*>(node->right->token);
            if((op_left != nullptr) && (op_right != nullptr)) {
                /* Left and right not an operator */
                int new_constant = 0;
                if(op->get_str() == "+") {
                    new_constant = std::stoi(node->left->token->get_str().data()) + std::stoi(node->right->token->get_str().data()); //TODO: need method in token to get value
                } else if(op->get_str() == "*") {
                    new_constant = std::stoi(node->left->token->get_str().data()) * std::stoi(node->right->token->get_str().data());
                }
                free(node->token);
                node->token = new Constant(std::to_string(new_constant)); //TODO: make constant token
                free(node->left);
                free(node->right);
                node->left = nullptr;
                node->right = nullptr;
                return 1;
            }
        }
    }
    /* Not an operator */
    return calculate_node(node->left) + calculate_node(node->right);
}

/* http://www2.imm.dtu.dk/courses/02198/slides/exprfold/foldexpr.pdf */
void ConstantFolding::calculate(TreeNode *root) {
    int folded_constants = 1;
    while(folded_constants > 0) {
        folded_constants = calculate_node(root);
    }

}
