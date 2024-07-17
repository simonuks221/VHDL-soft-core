#include "assembly.hpp"
#include <fstream>

void Assembly::assemble(std::span<ILine *> all_lines) {
    std::ofstream assembly_file("assembly.txt");
    if (!assembly_file) {
        std::cerr << "Error: Could not create the file." << std::endl;
        return;
    }
    for(ILine* line : all_lines) {
        for(const IToken * token : line->get_tokens()) {
            assembly_file << token->assemble_instruction() << std::endl;
        }
        assembly_file << std::endl;
    }

    assembly_file.close();
}