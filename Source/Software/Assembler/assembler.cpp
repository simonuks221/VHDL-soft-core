#include <iostream>
#include <fstream>
#include <string>
#include "commands/command_parser.hpp"
#include "preprocessing/preprocessor.hpp"

/* Removes comments, empty lines from inputs */
void read_lines(std::vector<std::string> &lines, std::ifstream &file) {
    std::string new_line;
    while (std::getline(file, new_line)) {
        if(new_line.empty()) {
            continue;
        }
        size_t comment_pos = new_line.find('#');

        if(comment_pos != std::string::npos) {
            new_line = new_line.substr(0, comment_pos);
        }
        lines.push_back(new_line);
    }
}

int main(int argc, char* argv[]) {
    /* Open file specified from input arguments */
    std::string file_path;
    if(argc != 2) {
        std::cerr << "Invalid amount of arguments" << std::endl;
        /* Use deafult path */
        file_path = "../assembly.txt";
    } else {
        file_path = argv[1];
    }
    /* Check if file correctly opened */
    std::ifstream inputFile(file_path);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file: " << file_path << std::endl;
        return 1;
    }

    std::vector<std::string> assembly_lines;
    read_lines(assembly_lines, inputFile);
    Preprocessor preprocessor;
    preprocessor.process_links(assembly_lines);
    // Preprocessor::process_links(assembly_lines);
    /* Output into file */
    std::ofstream binary_file("binary.txt");
    if (!binary_file) { //TODO: unify logging library
        std::cerr << "Error: Could not create the file" << std::endl;
        return 1;
    }
    /* Parse file line by line into output file */
    CommandParser::parse_lines(assembly_lines, binary_file);

    inputFile.close();
    binary_file.close();
    std::cout << "Success" <<std::endl;
    return 0;
}