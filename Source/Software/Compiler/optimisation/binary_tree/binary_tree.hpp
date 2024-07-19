#include "IOperator.hpp"
#include "line.hpp"
#include <stack>

#pragma once

class TreeNode {
    private:
        IToken *token;
        TreeNode *left;
        TreeNode *right;
    public:
        IToken *get_token(void);
        TreeNode *get_left(void);
        TreeNode *get_right(void);
        void set_left(TreeNode *_left);
        void set_right(TreeNode *_right);
        void set_token(IToken *_token);
        TreeNode(IToken *_token) : token(_token), left(nullptr), right(nullptr) {}
        ~TreeNode() = default;
};

class BinaryTree {
    private:
        static constexpr unsigned int token_spacing = 8;
        TreeNode* root;
        TreeNode* construct_tree_from_rpn(ILine *line);
        void printout_from_node(TreeNode* node, unsigned int rows, unsigned int collumns, unsigned int row, unsigned int collumn, TreeNode** tree_nodes_2d) const;
    public:
        BinaryTree(ILine *line);
        TreeNode* get_root(void) const;
        void printout_all(void) const;

        //TODO: should return to os instead of this, also make outside class
        friend std::ostream& operator<<(std::ostream& os, const BinaryTree& binary_tree) {
            binary_tree.printout_all();
            return os;
        }
};