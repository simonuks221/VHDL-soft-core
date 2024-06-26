#include <vector>
#include <string_view>

class CommandBase;

class CommandParser {
    private:
        static std::vector<CommandBase*> commands;
    public:
        CommandParser() = default;
        ~CommandParser() = default;
        bool parse_line(std::string_view line);
};

class CommandParserSingleton {
    public:
        /* Disallow copying and assigning */
        CommandParserSingleton(CommandParserSingleton &other) = delete;
        void operator=(const CommandParserSingleton &) = delete;
        CommandParserSingleton() = default;
        ~CommandParserSingleton() = default;
        static CommandParser & get_instance();
};