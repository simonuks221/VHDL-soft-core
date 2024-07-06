#include "IOperator.hpp"
#include <span>
#include <stack>

#pragma once

class TreeNode {
    public:
        Token *token;
        TreeNode *left;
        TreeNode *right;
        TreeNode(Token *_token) : token(_token), left(nullptr), right(nullptr) {}
};

class BinaryTree {
    private:
        static constexpr unsigned int representation_spacing = 10;
        TreeNode* root;
        TreeNode* construct_tree_from_rpn(std::span<Token*> rpn);
        void printout_from_node(TreeNode* node, int depth, std::vector<std::vector<TreeNode *>> &tree_nodes_2d);
    public:
        BinaryTree(std::span<Token*> tokens);
        TreeNode* get_root(void);
        void printout_all(void);
};