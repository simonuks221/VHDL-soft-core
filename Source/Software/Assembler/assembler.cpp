#include <iostream>
#include <fstream>
#include <string>
#include "command_parser.hpp"
#include "preprocessor.hpp"
#include "line.hpp"

/* Removes comments, empty lines from inputs */
void read_lines(std::vector<Line> &lines, std::ifstream &file) {
    std::string new_line_string;
    unsigned int assembly_line = 0;
    while (std::getline(file, new_line_string)) {
        assembly_line++;
        if(new_line_string.empty()) {
            continue;
        }
        size_t comment_pos = new_line_string.find('#');

        if(comment_pos != std::string::npos) {
            new_line_string = new_line_string.substr(0, comment_pos);
        }
        if(new_line_string.empty()) {
            continue;
        }
        Line new_line(assembly_line, new_line_string);
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
    std::vector<Line> assembly_lines;
    read_lines(assembly_lines, inputFile);
    /* Expand functions */
    CommandParser::expand_commands(assembly_lines);
    Preprocessor::process_links(assembly_lines);
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