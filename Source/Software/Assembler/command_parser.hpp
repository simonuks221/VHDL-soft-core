#include <vector>
#include <string_view>

class CommandParser {
    private:

    public:
        CommandParser() = default;
        ~CommandParser() = default;
        bool parse_line(std::string_view line);
};

class CommandParserSingleton {
    public:
        CommandParserSingleton(CommandParserSingleton &other) = delete;
        void operator=(const CommandParserSingleton &) = delete;
        CommandParserSingleton() = default;
        ~CommandParserSingleton() = default;
        void do_stuff();
        CommandParser & get_instance();
};