#include <cassert>
#include <string>
#include <iostream>
#include <cstring>
#include <sstream>
#include "preprocessor.hpp"

void Preprocessor::process_links(std::vector<Line> &lines) {
    find_all_links(lines);
    replace_all_links(lines);
    // add_link_loads_to_jump(lines);
}

void Preprocessor::find_all_links(std::vector<Line> &lines) {
    for(unsigned int i = 0; i < lines.size(); i++) {
        Line line = lines[i];
        std::string_view line_content = line.get_content();
        if(line_content[0] != '.') {
            continue;
        }
        if(all_links.find(line_content.data()) != all_links.end()) {
            unsigned int duplicate_line = all_links.at(line_content.data()); //TODO: lines wont match the original file lines
            std::cerr << "Multiple definitions of same link: " << line.get_assembly_line() << "at lines: " << duplicate_line << " and " << i << std::endl;
            assert(false);
        }
        /* New link found, add it and line number to map */
        all_links.insert_or_assign(line_content.data(), i);
        lines.erase(lines.begin() + i);
    }
}

void Preprocessor::replace_all_links(std::vector<Line> &lines) {
    for(unsigned int i = 0; i < lines.size(); i++) {
        Line line = lines[i];
        std::string_view line_content = line.get_content();
        /* Parse line for words */
        size_t prev = 0;
        size_t pos = 0;
        while ((pos = line_content.find_first_of(word_delimiters, prev)) != std::string::npos)
        {
            if (pos > prev) {
                replace_if_link(lines[i], prev, pos-prev);
            }
            prev = pos+1;
        }
        if (prev < line_content.length()) {
            replace_if_link(lines[i], prev, std::string::npos);
        }
    }
}

void Preprocessor::replace_if_link(Line &line, size_t start, size_t end) {
    std::string line_content = line.get_content().data();
    std::string link_word = line_content.substr(start, end);
    if(link_word[0] != '.') {
        return;
    }
    if(all_links.find(link_word) == all_links.end()) {
        std::cerr << "Invalid link without definition: " << link_word << std::endl;
        assert(false);
    }
    line_content.replace(start, end - start, std::to_string(all_links.at(link_word)));
    line.set_content(line_content);
}

// void Preprocessor::add_link_loads_to_jump(std::vector<std::string> &lines) {
//     static constexpr std::string load_cmd = "JUMP";
//     for(unsigned int i = 0; i < lines.size(); i++) {
//         std::string &line = lines[i];
//         if(std::strncmp(load_cmd.c_str(), line.c_str(), load_cmd.size()) != 0) {
//             continue;
//         }
//         /* Get third argument that is jump location */
//         //TODO: make nicer
//         // std::stringstream ss(line);
//         // std::string word;
//         // std::getline(ss, word, ' ');
//         // std::getline(ss, word, ' ');
//         // std::getline(ss, word, ' ');
//         // std::string load_cmd = "PUSH " + word;
//         // lines.insert(lines.begin() + i, load_cmd);
//         // i++;
//     }
// }
