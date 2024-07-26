#include "line.hpp"
#include <vector>

#pragma one

class CyclesResolver {
    private:

    public:
        CyclesResolver() {};
        ~CyclesResolver() = default;

        static bool resolve(std::vector<ILine *> &lines);
};