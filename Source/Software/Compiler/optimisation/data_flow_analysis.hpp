#include "line.hpp"
#include <set>

#pragma once

/* Confrol Flow Graph */
class CFGBlock {
    private:

    public:
        CFGBlock() {};
        ~CFGBlock() = default;

        std::set <IToken *> in;
        std::set <IToken *> out;
        //TODO: getters
};

/* Data flow analysis */
class DataFlowAnalysis {
    private:
        std::vector<CFGBlock> blocks;
    public:
        DataFlowAnalysis() {};
        ~DataFlowAnalysis() = default;
        void analyze(std::vector<ILine *> &all_lines);
};
