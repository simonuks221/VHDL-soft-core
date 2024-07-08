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
    if((node1->get_token()->get_type() != eToken::Constant) || (node2->get_token()->get_type() != eToken::Constant)) {
        /* Both nodes aren't constant */
        return false;
    }
    Constant *const1 = dynamic_cast<Constant*>(node1->get_token());
    Constant *const2 = dynamic_cast<Constant*>(node2->get_token());
    assert(const1 != nullptr);
    assert(const2 != nullptr);
    int new_constant = 0;
    if(replace_node->get_token()->get_str() == "+") {
        new_constant = std::stoi(const1->get_str().data()) + std::stoi(const2->get_str().data()); //TODO: need method in token to get value
    } else if(replace_node->get_token()->get_str() == "*") {
        new_constant = std::stoi(const1->get_str().data()) * std::stoi(const2->get_str().data());
    }
    free(replace_node->get_token());
    replace_node->set_token(new Constant(std::to_string(new_constant))); //TODO: make constant token
    return true;
}

static int calculate_node(TreeNode* node) { //TODO: namespace, //TODO: do several operations at once
    if ((node == nullptr) || (node->get_left() == nullptr) || (node->get_right() == nullptr)) {
        return 0;
    }
    /* Check if operator */
    if(node->get_token()->get_type() == eToken::Operator) {
        IOperator *op = dynamic_cast<IOperator*>(node->get_token());
        assert(op != nullptr);
        if((op->get_str() == "+") || (op->get_str() == "*")) { //TODO: remove hardcode
            /* Try fold two children */
            if(fold_constants(node->get_left(), node->get_right(), node)) {
                free(node->get_left()); //TODO: on node destroy free its token else MEMORY LEAK
                free(node->get_right());
                node->set_left(nullptr);
                node->set_right(nullptr);
                return 1;
            }
            /* Try push all constants to left */
            if((node->get_right()->get_token()->get_type() == eToken::Constant) && (node->get_left()->get_token()->get_type() != eToken::Constant)) {
                /* Swap left to right */
                TreeNode *temp_swap = node->get_right();
                node->set_right(node->get_left());
                node->set_left(temp_swap);
                return 1;
            }
            /* Try fold if bottom left is same operator with constant in its left
             * only applicable if moves are commutative and associative */
            if(node->get_right()->get_token()->get_type() == eToken::Operator) {
                IOperator *op_left = dynamic_cast<IOperator*>(node->get_right()->get_token());
                assert(op_left != nullptr);
                if(op_left->get_str() == op->get_str()) {
                    /* Left operator same as this operator, try fold its left children */
                    TreeNode *left_nonconstant = node->get_right()->get_right();
                    if(fold_constants(node->get_right()->get_left(), node->get_left(), node->get_right())) {
                        free(node->get_right()->get_left());
                        node->get_right()->set_left(nullptr);
                        node->get_right()->set_right(nullptr);
                        free(node->get_left());
                        node->set_left(left_nonconstant);
                        return 1;
                    }
                }
            }
            /* Move constants up if moves are commutative and associative */
            if(node->get_left()->get_token()->get_type() == eToken::Operator) {
                IOperator *op_left = dynamic_cast<IOperator*>(node->get_left()->get_token());
                assert(op_left != nullptr);
                if(op_left->get_str() == op->get_str()) {
                    if(node->get_right()->get_token()->get_type() != eToken::Constant) {
                        /* Could change into constant node->get_right() */
                        if(node->get_left()->get_left()->get_token()->get_type() == eToken::Constant) {
                            /* Swap node->get_left()->get_left() with node->get_right() */
                            IToken *temp_swap = node->get_left()->get_left()->get_token();
                            node->get_left()->get_left()->set_token(node->get_right()->get_token());
                            node->get_right()->set_token(temp_swap);
                            return 1;
                        }
                        if(node->get_left()->get_right()->get_token()->get_type() == eToken::Constant) {
                            /* Swap node->get_left()->get_right() with node->get_right() */
                            IToken *temp_swap = node->get_left()->get_right()->get_token();
                            node->get_left()->get_right()->set_token(node->get_right()->get_token());
                            node->get_right()->set_token(temp_swap);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    /* Not an operator */
    return calculate_node(node->get_left()) + calculate_node(node->get_right());
}

/* http://www2.imm.dtu.dk/courses/02198/slides/exprfold/foldexpr.pdf */
void ConstantFolding::calculate(TreeNode *root) {
    int folded_constants = 1;
    while(folded_constants > 0) {
        folded_constants = calculate_node(root);
    }

}
