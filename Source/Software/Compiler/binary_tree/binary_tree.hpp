#include "IOperator.hpp"
#include <span>
#include <stack>

#pragma once

class TreeNode {
    public:
        IToken *token;
        TreeNode *left;
        TreeNode *right;
        TreeNode(IToken *_token) : token(_token), left(nullptr), right(nullptr) {}
};

class BinaryTree {
    private:
        static constexpr unsigned int representation_spacing = 10;
        TreeNode* root;
        TreeNode* construct_tree_from_rpn(std::span<IToken*> rpn);
        void printout_from_node(TreeNode* node, unsigned int rows, unsigned int collumns, unsigned int row, unsigned int collumn, TreeNode** tree_nodes_2d);
    public:
        BinaryTree(std::span<IToken*> tokens);
        TreeNode* get_root(void);
        void printout_all(void);
};