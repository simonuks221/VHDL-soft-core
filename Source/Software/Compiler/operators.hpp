#include "IOperator.hpp"
#include <string_view>
#include <string>

class IgnoreOperator : public IOperator {
    public:
        IgnoreOperator(std::string _str) : IOperator(_str, 0, true) {};
        ~IgnoreOperator() = default;
};

class FunctionOperator : public IOperator {
    public:
        FunctionOperator(std::string _str) : IOperator(_str, 0, true) {};
        ~FunctionOperator() = default;
};

class BaseOperator : public IOperator {
    public:
        BaseOperator(std::string _str, unsigned int _presedence, bool _left) : IOperator(_str, _presedence, _left) {};
        ~BaseOperator() = default;
};
