#include <cassert>
#include <string>
#include <iostream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include "preprocessor.hpp"
#include "logging.hpp"

std::unordered_map<std::string, ICommand *> Preprocessor::all_links;

void Preprocessor::find_all_links(std::vector<std::unique_ptr<ICommand>> &commands) {
    /* Can't have link at first line */ //TODO: might be issue
    for(unsigned int i = 0; i < commands.size(); i++) {
        CommandLink *link_command = dynamic_cast<CommandLink *>(commands[i].get());
        if(link_command == nullptr) {
            continue;
        }
        if(all_links.find(link_command->link) != all_links.end()) {
            // ICommand *duplicate = all_links.at(link_command->link);
            Logging::err("Multiple definitions of same link: " + link_command->link);
            assert(false);
        }
        /* New link found, add it and line number to map */
        all_links.insert_or_assign(link_command->link, commands[i-1].get());
    }
}

void Preprocessor::inform_all_links(std::vector<std::unique_ptr<ICommand>> &commands) {
    for(unsigned int i = 0; i < commands.size(); i++) {
        CommandPush *push_command = dynamic_cast<CommandPush *>(commands[i].get());
        if(push_command == nullptr) {
            continue;
        }
        if(!std::holds_alternative<std::string>(push_command->constant)) {
            continue;
        }
        if(all_links.find(std::get<std::string>(push_command->constant)) == all_links.end()) {
            Logging::err("Invalid link without definition: " + std::get<std::string>(push_command->constant));
            assert(false);
        }
        const ICommand *target_command = all_links.at(std::get<std::string>(push_command->constant));
        auto link_command = std::find_if(commands.begin(), commands.end(),
            [target_command](const std::unique_ptr<ICommand> &cmd) {
                return cmd.get() == target_command;
            });
        if(link_command == commands.end()) {
            Logging::err("Invalid link command");
            assert(false);
        }
        int link_line = static_cast<int>(std::distance(commands.begin(), link_command));
        int line_diff = link_line - static_cast<int>(i);
        push_command->will_be_signed_link = line_diff < 0;
        push_command->will_be_big_link = line_diff > 127;
        push_command->link_updated = true;
    }
}

void Preprocessor::replace_all_links(std::vector<std::unique_ptr<ICommand>> &commands) {
    for(unsigned int i = 0; i < commands.size(); i++) {
        CommandPush *push_command = dynamic_cast<CommandPush *>(commands[i].get());
        if(push_command == nullptr) {
            continue;
        }
        if(!std::holds_alternative<std::string>(push_command->constant)) {
            continue;
        }
        replace_if_link(push_command, i, commands);
    }
}

void Preprocessor::replace_if_link(CommandPush *this_command, unsigned int current_line, std::vector<std::unique_ptr<ICommand>> &commands) {
    if(all_links.find(std::get<std::string>(this_command->constant)) == all_links.end()) {
        Logging::err("Invalid link without definition: " + std::get<std::string>(this_command->constant));
        assert(false);
    }
    ICommand *target_command = all_links.at(std::get<std::string>(this_command->constant));
    auto it = std::find_if(commands.begin(), commands.end(),
                           [target_command](const std::unique_ptr<ICommand> &cmd) {

                               return cmd.get() == target_command;
                           });
    if(it == commands.end()) {
        Logging::err("Invalid link command");
        assert(false);
    }

    int link_line = static_cast<int>(std::distance(commands.begin(), it));
    int line_diff = link_line - static_cast<int>(current_line);
    this_command->constant = line_diff;
    this_command->signed_constant = line_diff < 0;
}
