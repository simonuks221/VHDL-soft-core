#include <string_view>
#include <string>
#include <stack>
#include <vector>
#include "token.hpp"

class IOperator : public Token {
    private:
        unsigned int presedence;
        bool left_associative;
    public:
        IOperator(std::string _str, unsigned int _presedence, bool _left) : Token(_str),
                presedence(_presedence), left_associative(_left) {};
        virtual ~IOperator() = default;

        unsigned int get_presedence(void) const;
        bool get_left_associative(void) const;
        //TODO: make static
        virtual void shunting_yard_action(std::stack<IOperator*> &operator_stack, std::vector<Token*> &output) const = 0;
};