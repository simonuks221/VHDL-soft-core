#include "binary_tree.hpp"
#include <vector>

BinaryTree::BinaryTree(std::span<Token*> tokens) {
    TreeNode *root = construct_tree_from_rpn(tokens);
}

TreeNode* BinaryTree::construct_tree_from_rpn(std::span<Token*> rpn) {
    for(Token *token : rpn) {
        IOperator *op = dynamic_cast<IOperator*>(token);
        if(op != nullptr) {
            /* Is an operator */
            TreeNode* node = new TreeNode(token);
            node->right = nodes.top();
            nodes.pop();
            node->left = nodes.top();
            nodes.pop();
            nodes.push(node);
        } else {
            /* Not an operator */
            nodes.push(new TreeNode(token));
        }
    }

    return nodes.top();
}

void BinaryTree::printout_all() {

    std::vector<std::vector<TreeNode *>> tree_nodes_2d; //TODO: optimise by preallocating space
    TreeNode *root = nodes.top();
    printout_from_node(root, 0, tree_nodes_2d);
    /* Get tree max width */
    unsigned int max_width = 0;
    for(std::vector<TreeNode *> this_depth_nodes : tree_nodes_2d) {
        if(this_depth_nodes.size() > max_width) {
            max_width = this_depth_nodes.size();
        }
    }
    /* Printout from tree */
    for(std::vector<TreeNode *> this_depth_nodes : tree_nodes_2d) {
        unsigned int this_row_spacing = max_width * 10 / this_depth_nodes.size();
        for(TreeNode * this_node : this_depth_nodes) {
            std::string spacing(this_row_spacing, ' ');
            std::cout << spacing << this_node->token->get_str() << " ";
        }
        std::cout << std::endl;
    }
}

void BinaryTree::printout_from_node(TreeNode* node, int depth, std::vector<std::vector<TreeNode *>> &tree_nodes_2d) {
    if (node == nullptr) return;
    /* Add another entry if new depth reached */
    if(depth >= tree_nodes_2d.size()) {
        tree_nodes_2d.push_back(std::vector<TreeNode *>());
    }
    /* Add node to 2d tree */
    tree_nodes_2d.at(depth).push_back(node);
    //std::cout << node->token->get_str() << std::endl;
    printout_from_node(node->left, depth + 1, tree_nodes_2d);
    printout_from_node(node->right, depth + 1, tree_nodes_2d);
    // if (node == nullptr) return;
    // printout_from_node(node->right, depth + 1);
    // for (int i = 0; i < depth; ++i) std::cout << "    ";
    // std::cout << node->token->get_str() << std::endl;
    // printout_from_node(node->left, depth + 1);
}