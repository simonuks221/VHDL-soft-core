#include "line.hpp"
#include <set>
#include <vector>

#pragma once

/* Confrol Flow Graph */
class CFGBlock {
    private:

    public:
        CFGBlock() {};
        ~CFGBlock() = default;

        std::vector<CFGBlock *> next;
        std::vector<CFGBlock *> previous;
        std::vector<ILine *> lines;
};

/* Data flow analysis */
class DataFlowAnalysis {
    private:
        CFGBlock *root = nullptr;
    public:
        DataFlowAnalysis() {};
        ~DataFlowAnalysis() = default;
        void analyze(std::vector<ILine *> &all_lines);
};
