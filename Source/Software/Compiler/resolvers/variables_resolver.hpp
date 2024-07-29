#include "line.hpp"
#include <vector>
#include <unordered_map>

#pragma one

class VariablesResolver {
    private:
        std::unordered_map<std::string_view, Variable *> variable_map;
    public:
        VariablesResolver() {};
        ~VariablesResolver() = default;

        bool resolve(std::vector<ILine *> &lines);

        //TODO: actual singleton
        static VariablesResolver &get_instance(void);
};