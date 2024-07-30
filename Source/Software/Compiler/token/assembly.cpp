#include "assembly.hpp"
#include "logging.hpp"
#include <string_view>
#include <fstream>

void Assembly::assemble(std::span<ILine *> all_lines) {
    std::ofstream assembly_file("assembly.txt");
    if (!assembly_file) {
        Logging::error("Error: Could not create the file");
        return;
    }
    for(ILine* line : all_lines) {
        for(const IToken * token : line->get_tokens()) {
            const ITokenAssemblable *assemblable_token = dynamic_cast<const ITokenAssemblable *>(token);
            if(assemblable_token == nullptr) {
                continue;
            }
            std::string_view new_line = assemblable_token->assemble_instruction();
            if(!new_line.empty()) {
                assembly_file << new_line << std::endl;
            }
        }
        assembly_file << std::endl;
    }

    assembly_file.close();
}