#include <cassert>
#include <string>
#include <iostream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include "preprocessor.hpp"

std::unordered_map<std::string, ICommand *> Preprocessor::all_links {};

void Preprocessor::process_links(std::vector<ICommand *> &commands) {
    find_all_links(commands);
    replace_all_links(commands);
    // add_link_loads_to_jump(lines);
}

void Preprocessor::find_all_links(std::vector<ICommand *> &commands) {
    /* Can't have link at first line */ //TODO: might be issue
    for(unsigned int i = 1; i < commands.size(); i++) {
        CommandLink *link_command = dynamic_cast<CommandLink *>(commands[i]);
        if(link_command == nullptr) {
            continue;
        }
        if(all_links.find(link_command->link) != all_links.end()) {
            ICommand *duplicate = all_links.at(link_command->link);
            std::cerr << "Multiple definitions of same link: " << link_command->link << "at lines: " << " and " << i << std::endl;
            assert(false);
        }
        /* New link found, add it and line number to map */
        all_links.insert_or_assign(link_command->link, commands[i-1]);
        //TODO: free the ereased member or make unique ptr
        // commands.erase(commands.begin() + i);
    }
}

void Preprocessor::replace_all_links(std::vector<ICommand *> &commands) {
    for(unsigned int i = 0; i < commands.size(); i++) {
        CommandPush *push_command = static_cast<CommandPush *>(commands[i]);
        if(push_command == nullptr) {
            continue;
        }
        if(!std::holds_alternative<std::string>(push_command->constant)) {
            continue;
        }
        replace_if_link(push_command, i, commands);
    }
}

void Preprocessor::replace_if_link(CommandPush *command, unsigned int current_line, std::vector<ICommand *> &commands) {
    if(all_links.find(std::get<std::string>(command->constant)) == all_links.end()) {
        std::cerr << "Invalid link without definition: " << std::get<std::string>(command->constant) << std::endl;
        assert(false);
    }
    auto link_command = std::find(commands.begin(), commands.end(), all_links.at(std::get<std::string>(command->constant)));
    if(link_command == commands.end()) {
        std::cerr << "Invalid link command" << std::endl;
        assert(false);
    }

    unsigned int link_line = std::distance(commands.begin(), link_command);
    int line_diff = link_line - current_line;
    /* TODO: workaround for signed link stuff */
    if(line_diff < 0) {
        line_diff -= 2;
    }
    //TODO: will only work on push commands TODO:fix
    command->constant = line_diff;
    command->signed_constant = line_diff < 0;
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
