#include "assembly.hpp"
#include <fstream>

void Assembly::assemble(std::span<std::vector<IToken*>> all_tokens) {
    std::ofstream assembly_file("assembly.txt");
    if (!assembly_file) {
        std::cerr << "Error: Could not create the file." << std::endl;
        return;
    }
    for(std::vector<IToken*> token_line : all_tokens) {
        for(IToken * token : token_line) {
            assembly_file << token->assemble_instruction() << std::endl;
        }
        assembly_file << std::endl;
    }

    assembly_file.close();
}