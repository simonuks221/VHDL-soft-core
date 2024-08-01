#include <cassert>
#include <string>
#include <iostream>
#include "preprocessor.hpp"

void Preprocessor::process_links(std::vector<std::string> &lines) {
    find_all_links(lines);
    replace_all_links(lines);
}

void Preprocessor::find_all_links(std::vector<std::string> &lines) {
    for(unsigned int i = 0; i < lines.size(); i++) {
        std::string_view line = lines[i];
        if(line[0] != '.') {
            continue;
        }
        if(all_links.find(line.data()) != all_links.end()) {
            unsigned int duplicate_line = all_links.at(line.data()); //TODO: lines wont match the original file lines
            std::cerr << "Multiple definitions of same link: " << line << "at lines: " << duplicate_line << " and " << i << std::endl;
            assert(false);
        }
        /* New link found, add it and line number to map */
        all_links.insert_or_assign(line.data(), i);
        lines.erase(lines.begin() + i);
    }
}

void Preprocessor::replace_all_links(std::vector<std::string> &lines) {
    for(unsigned int i = 0; i < lines.size(); i++) {
        std::string_view line = lines[i];
        /* Parse line for words */
        size_t prev = 0;
        size_t pos = 0;
        while ((pos = line.find_first_of(word_delimiters, prev)) != std::string::npos)
        {
            if (pos > prev) {
                replace_if_link(lines[i], prev, pos-prev);
            }
            prev = pos+1;
        }
        if (prev < line.length()) {
            replace_if_link(lines[i], prev, std::string::npos);
        }
    }
}

void Preprocessor::replace_if_link(std::string &line, size_t start, size_t end) {
    std::string link_word = line.substr(start, end);
    if(link_word[0] != '.') {
        return;
    }
    if(all_links.find(link_word) == all_links.end()) {
        std::cerr << "Invalid link without definition: " << link_word << std::endl;
        assert(false);
    }
    line.replace(start, end - start, std::to_string(all_links.at(link_word)));
}
