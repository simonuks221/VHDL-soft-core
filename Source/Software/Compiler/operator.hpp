#include <string_view>
#include <string>
class Operator {
    private:
        std::string str;
        unsigned int presedence;
        bool left_associative;
    public: //TODO: getters/setters
        Operator(std::string _str, unsigned int _presedence, bool _left) :
                str(_str), presedence(_presedence), left_associative(_left) {};
        ~Operator() = default;

        std::string_view get_str(void) const;
        unsigned int get_presedence(void) const;
        bool get_left_associative(void) const;
};