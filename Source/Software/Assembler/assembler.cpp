#include <iostream>
#include <fstream>
#include <string>
#include "command_parser.hpp"

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
    CommandParserSingleton command_parser;
    //command_parser.do_stuff();
    //CommandParser &command_parser = CommandParserSingleton::get_instance();
    CommandParser parser;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
        parser.parse_line(line);
    }

    inputFile.close();

    return 0;
}