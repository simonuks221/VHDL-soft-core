#include <unordered_map>
#include <string_view>

class CommandBase;

class CommandParser {
    private:
        static std::unordered_map<std::string_view, CommandBase*> commands;

        CommandBase *try_parse_token(std::string_view token);
    public:
        CommandParser() = default;
        ~CommandParser() = default;

        void add_command(CommandBase *new_command);
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