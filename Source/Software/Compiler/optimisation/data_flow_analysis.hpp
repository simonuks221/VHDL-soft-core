#include "line.hpp"
#include <set>
#include <vector>
#include <span>

#pragma once

/* Confrol Flow Graph */
class CFGBlock {
    private:
        std::vector<CFGBlock *> next;
        std::vector<CFGBlock *> previous;
        std::vector<ILine *> lines;
    public:
        CFGBlock() {};
        ~CFGBlock() = default;

        const std::vector<CFGBlock *> get_next(void) const;
        const std::vector<CFGBlock *> get_prev(void) const;
        const std::vector<ILine *> get_lines(void) const;

        void add_line(ILine *new_line);
        void add_prev(CFGBlock *new_prev);
        void add_next(CFGBlock *new_next);
};

/* Data flow analysis */
class DataFlowAnalysis {
    private:
        CFGBlock *root = nullptr;

        IToken *find_if_defined(const IToken *variable, const CFGBlock *start_block) const;
    public:
        DataFlowAnalysis() {};
        ~DataFlowAnalysis() = default;
        void analyze(std::vector<ILine *> &all_lines);
};
