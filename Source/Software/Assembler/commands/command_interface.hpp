#include <string_view>

class CommandInterface {
    public:
        CommandInterface() = default;
        ~CommandInterface() = default;
        virtual bool is_valid(std::string_view input) = 0;
};