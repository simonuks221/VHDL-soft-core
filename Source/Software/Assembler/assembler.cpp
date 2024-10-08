#include <iostream>
#include <fstream>
#include <string>
#include "command_parser.hpp"
#include "line.hpp"
#include "spellcheck.hpp"
#include "preprocessor.hpp"
#include "logging.hpp"

/* Removes comments, empty lines from inputs */
void read_lines(std::vector<std::unique_ptr<Line>> &lines, std::ifstream &file) {
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
        std::unique_ptr<Line> new_line = std::make_unique<Line>(assembly_line, new_line_string);
        lines.push_back(std::move(new_line));
    }
}

int main(int argc, char* argv[]) {
    Logging::info("Starting");
    /* Open file specified from input arguments */
    std::string file_path;
    if(argc != 2) {
        Logging::err("Invalid amount of arguments");
        /* Use deafult path */
        file_path = "../assembly.txt";
    } else {
        file_path = argv[1];
    }
    /* Check if file correctly opened */
    std::ifstream inputFile(file_path);
    if (!inputFile.is_open()) {
        Logging::err("Failed to open the file: " + file_path);
        return 1;
    }
    std::vector<std::unique_ptr<Line>> assembly_lines;
    std::vector<std::unique_ptr<ICommand>> assembly_commands;
    read_lines(assembly_lines, inputFile);
    inputFile.close();
    CommandParser::parse_commands(assembly_lines, assembly_commands);
    /* Expand complex commands */
    CommandParser::expand_commands_recursive(assembly_commands);
    /* Find all links and update their expected (not final) sizes, prepare for link preallocation */
    Preprocessor::find_all_links(assembly_commands);
    Preprocessor::inform_all_links(assembly_commands);
    /* Expand complex commands, preallocate links */
    CommandParser::expand_commands_recursive(assembly_commands);
    /* Find and store all links */
    Preprocessor::replace_all_links(assembly_commands);
    /* Expand again the final time - replace preallocated jump pushes with actual values */
    CommandParser::expand_commands(assembly_commands);
    /* Output into file */
    std::ofstream binary_file("binary.txt");
    if (!binary_file) {
        Logging::err("Error: Could not create the file");
        return 1;
    }
    /* Parse file line by line into output file */
    CommandParser::assemble_commands(assembly_commands, binary_file);
    binary_file.close();
    Logging::info("Success");
    return 0;
}
