#include "binary_tree.hpp"
#include <vector>
#include <cassert>
#include <cmath>

IToken * TreeNode::get_token(void) {
    return token;
}
TreeNode *TreeNode::get_left(void) {
    return left;
}
TreeNode *TreeNode::get_right(void) {
    return right;
}

void TreeNode::set_left(TreeNode *_left) {
    left = _left;
}

void TreeNode::set_right(TreeNode *_right) {
    right = _right;
}

void TreeNode::set_token(IToken *_token) {
    token = _token;
}

BinaryTree::BinaryTree(std::span<IToken*> tokens) {
    root = construct_tree_from_rpn(tokens);
}

TreeNode* BinaryTree::construct_tree_from_rpn(std::span<IToken*> rpn) {
    std::stack<TreeNode*> nodes;
    for(IToken *token : rpn) {
        if(token->get_type() == eToken::Operator) {
            /* Is an operator */
            IOperator *op = dynamic_cast<IOperator*>(token);
            assert(op != nullptr);
            TreeNode* node = new TreeNode(token);
            node->set_right(nodes.top());
            nodes.pop();
            node->set_left(nodes.top());
            nodes.pop();
            nodes.push(node);
        } else {
            /* Not an operator */
            nodes.push(new TreeNode(token));
        }
    }
    return nodes.top();
}

/* Returns count of rows (heigth of tree), does not count from 0 */
static unsigned int get_max_heigth(TreeNode * root) {
    if((root->get_left() == nullptr) || (root->get_right() == nullptr)) {
        return 1;
    }
    return std::max(get_max_heigth(root->get_left()), get_max_heigth(root->get_right()))+1;
}

/* Gets max width of the tree */ //TODO: now returns theoretical max width, not actual as some branches could be empty
static unsigned int get_max_width(unsigned int heigth) {
    return std::pow(2, (heigth-1));
}

void BinaryTree::printout_all() {
    if(root == nullptr) {
        return;
    }
    unsigned int max_heigth = get_max_heigth(root);
    unsigned int max_width = get_max_width(max_heigth);
    std::cout << "Tree heigth: " << max_heigth << ", width: " << max_width <<std::endl;
    TreeNode * tree_nodes_2d[max_width][max_heigth];
    for(unsigned int x = 0; x < max_width; x++) {
        for(unsigned int y = 0; y < max_heigth; y++) {
            tree_nodes_2d[x][y] = nullptr;
        }
    }
    printout_from_node(root, max_heigth, max_width, 0, 0, tree_nodes_2d[0]);
    /* Printout from tree */
    unsigned int token_space = 5;
    for(unsigned int y = 0; y < max_heigth; y++) {
        std::string row_spacing((max_heigth - y)*token_space/2, ' ');
        std::cout << row_spacing;
        for(unsigned int x = 0; x < max_width; x++) {
            TreeNode * node = tree_nodes_2d[x][y];
            if(node == nullptr) {
                std::cout << std::string(token_space, ' ');
                continue;
            }
            std::cout << node->get_token()->get_str() << std::string(token_space - node->get_token()->get_str().size(), ' ');
        }
        std::cout << std::endl;
    }
}

void BinaryTree::printout_from_node(TreeNode* node, unsigned int rows, unsigned int collumns, unsigned int row, unsigned int collumn, TreeNode** tree_nodes_2d) {
    if(node == nullptr) {
        return;
    }
    *(tree_nodes_2d + rows * collumn + row) = node;
    printout_from_node(node->get_left(), rows, collumns, row + 1, collumn, tree_nodes_2d);
    printout_from_node(node->get_right(), rows, collumns, row + 1, collumn + 1, tree_nodes_2d);
}

TreeNode* BinaryTree::get_root(void) {
    return root;
}