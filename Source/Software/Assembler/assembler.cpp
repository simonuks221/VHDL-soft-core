#include <iostream>
#include <fstream>
#include <string>
#include "commands/command_parser.hpp"
#include "commands/commands.hpp"

int main(int argc, char* argv[]) {
    /* Open file specified from input arguments */
    std::string file_path;
    if(argc != 2) {
        std::cerr << "Invalid amount of arguments" << std::endl;
        /* Use deafult path */
        file_path = "../code.txt";
    } else {
        file_path = argv[1];
    }
    /* Check if file correctly opened */
    std::ifstream inputFile(file_path);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file: " << file_path << std::endl;
        return 1;
    }
    /* Parse file line by line */
    CommandLoad();

    CommandParser &command_parser = CommandParserSingleton::get_instance();
    std::string line;
    while (std::getline(inputFile, line)) {
        command_parser.parse_line(line);
    }

    inputFile.close();

    return 0;
}