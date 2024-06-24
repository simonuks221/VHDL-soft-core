#include <string>
#include "command_interface.hpp"

class CommandBase : CommandInterface {
    private:
        std::string codeword;
    public:
        CommandBase(std::string _codeword);
        ~CommandBase() = default;
        bool is_valid(std::string_view input) override;
};
