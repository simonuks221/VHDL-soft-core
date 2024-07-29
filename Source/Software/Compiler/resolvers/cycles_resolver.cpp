#include "cycles_resolver.hpp"
#include "keywords.hpp"
#include <cassert>
#include <algorithm>

bool CyclesResolver::resolve(std::vector<ILine *> &lines) {
    /* Find all block transition keywords */
    for(ILine *line : lines) {
        for(IToken *token : line->get_tokens()) {
            if(token->get_type() != eToken::Keyword) {
                continue;
            }
            ITokenScopeTransition *transition = dynamic_cast<ITokenScopeTransition *>(token);
            if(transition == nullptr) {
                continue;
            }
            if(!transition->parse_for_brace(line->get_tokens())) {
                std::cerr << "Failed to parse for while braces " << std::endl;
                assert(false);
                return false;
            }
            /* Insert start brace at the start of the line - so the jump tp it would envelop argument loading */
            CurlyBracesKeyword *start_brace = transition->get_start_barce();
            auto it = std::find(line->get_tokens().begin(), line->get_tokens().end(), start_brace);
            if(it == line->get_tokens().end()) {
                std::cerr << "Failed to refind brace in line" << std::endl;
                assert(false);
            }
            line->get_tokens().erase(it);
            line->get_tokens().insert(line->get_tokens().begin(), start_brace);

            if(transition->get_should_repeat()) {
                /* Add return to while at block end - search for the lines of block end brace */
                IToken *brace_to_find = transition->get_start_barce()->get_other();
                for(ILine *find_line : lines) {
                    auto it = std::find(find_line->get_tokens().begin(), find_line->get_tokens().end(), brace_to_find);
                    if(it == find_line->get_tokens().end()) {
                        continue;
                    }
                    /* Make goto at the end of block to point to start condition */
                    GotoKeyword *goto_keyword = new GotoKeyword();
                    goto_keyword->set_destination(transition->get_start_barce());
                    find_line->get_tokens().insert(it, goto_keyword);
                    break;
                } //TODO: clean up into functions
            }
            break; //TODO: will not work with 2 whiles in one line
        }
    }
    return true;
}