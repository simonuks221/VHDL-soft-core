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
            const ITokenAssemblable *assemblable_token = dynamic_cast<const ITokenAssemblable *>(token);
            if(assemblable_token == nullptr) {
                continue;
            }
            assembly_file << assemblable_token->assemble_instruction() << std::endl;
        }
        assembly_file << std::endl;
    }

    assembly_file.close();
}