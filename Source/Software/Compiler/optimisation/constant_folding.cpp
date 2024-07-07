#include "constant_folding.hpp"
#include <cassert>

ConstantFolding::ConstantFolding() {

}

/* Checks if node1 and node2 are constants and replace node is an operator,
 * folds constants if all criteria met.
 * Returns true if fold succesfull.  */
static bool fold_constants(TreeNode* node1, TreeNode* node2, TreeNode* replace_node) {
    if((replace_node == nullptr) || (node1 == nullptr) || (node2 == nullptr)) {
        return false;
    }
    if((node1->token->get_type() != eToken::Constant) || (node2->token->get_type() != eToken::Constant)) {
        /* Both nodes aren't constant */
        return false;
    }
    Constant *const1 = dynamic_cast<Constant*>(node1->token);
    Constant *const2 = dynamic_cast<Constant*>(node2->token);
    assert(const1 != nullptr);
    assert(const2 != nullptr);
    int new_constant = 0;
    if(replace_node->token->get_str() == "+") {
        new_constant = std::stoi(const1->get_str().data()) + std::stoi(const2->get_str().data()); //TODO: need method in token to get value
    } else if(replace_node->token->get_str() == "*") {
        new_constant = std::stoi(const1->get_str().data()) * std::stoi(const2->get_str().data());
    }
    free(replace_node->token);
    replace_node->token = new Constant(std::to_string(new_constant)); //TODO: make constant token
    return true;
}

static int calculate_node(TreeNode* node) { //TODO: namespace, //TODO: do several operations at once
    if ((node == nullptr) || (node->left == nullptr) || (node->right == nullptr)) {
        return 0;
    }
    /* Check if operator */
    if(node->token->get_type() == eToken::Operator) {
        IOperator *op = dynamic_cast<IOperator*>(node->token);
        assert(op != nullptr);
        if((op->get_str() == "+") || (op->get_str() == "*")) { //TODO: remove hardcode
            /* Try fold two children */
            if(fold_constants(node->left, node->right, node)) {
                free(node->left); //TODO: on node destroy free its token else MEMORY LEAK
                free(node->right);
                node->left = nullptr;
                node->right = nullptr;
                return 1;
            }
            /* Try push all constants to left */
            if((node->right->token->get_type() == eToken::Constant) && (node->left->token->get_type() != eToken::Constant)) {
                std::swap(node->right, node->left);
                return 1;
            }
            /* Try fold if bottom left is same operator with constant in its left
             * only applicable if moves are commutative and associative */
            if(node->right->token->get_type() == eToken::Operator) {
                IOperator *op_left = dynamic_cast<IOperator*>(node->right->token);
                assert(op_left != nullptr);
                if(op_left->get_str() == op->get_str()) {
                    /* Left operator same as this operator, try fold its left children */
                    TreeNode *left_nonconstant = node->right->right;
                    if(fold_constants(node->right->left, node->left, node->right)) {
                        free(node->right->left);
                        node->right->left = nullptr;
                        node->right->right = nullptr;
                        free(node->left);
                        node->left = left_nonconstant;
                        return 1;
                    }
                }
            }
            /* Move constants up if moves are commutative and associative */
            if(node->left->token->get_type() == eToken::Operator) {
                IOperator *op_left = dynamic_cast<IOperator*>(node->left->token);
                assert(op_left != nullptr);
                if(op_left->get_str() == op->get_str()) {
                    if(node->right->token->get_type() != eToken::Constant) {
                        /* Could change into constant node->right */
                        if(node->left->left->token->get_type() == eToken::Constant) {
                            /* Swap node->left->left with node->right */
                            std::swap(node->left->left->token, node->right->token);
                            return 1;
                        }
                        if(node->left->right->token->get_type() == eToken::Constant) {
                            /* Swap node->left->right with node->right */
                            std::swap(node->left->right->token, node->right->token);
                            return 1;
                        }
                    }
                }
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
