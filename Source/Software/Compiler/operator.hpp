
class Operator {
    public: //TODO: getters/setters
        Operator(char _ch, unsigned int _presedence, bool _left) :
                ch(_ch), presedence(_presedence), left_associative(_left) {};
        ~Operator() = default;

        char ch;
        unsigned int presedence;
        bool left_associative;
};