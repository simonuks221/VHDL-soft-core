#include "token.hpp"
#include "tokenizer.hpp"
#include "keywords.hpp"
#include <cassert>

/* Token */

IToken *Token::clone(void) const {
    return new Token(*this);
}

eToken Token::get_type(void) const {
    return eToken::Invalid;
}

unsigned int Token::get_input_amount(void) const {
    return input_amount;
}

std::string_view Token::get_str() const {
    return str;
}

unsigned int Token::get_presedence() const {
    return presedence;
}

bool Token::get_left_associative() const {
    return left_associative;
}

void Token::shunting_yard_action(std::stack<IToken*> &operator_stack, std::vector<IToken*> &output, IToken *current) const {
    output.push_back(current);
}

/* Variable */

IToken *Variable::clone() const {
    return new Variable(*this);
}

eToken Variable::get_type(void) const {
    return eToken::Variable;
}

bool Variable::get_is_declaration(void) const {
    return is_declaration;
}

void Variable::set_is_declaration(bool declaration) {
    is_declaration = declaration;
}


std::string_view Variable::assemble_instruction(void) const {
    if(is_declaration) {
        /* No need to load from memory if declaration */
        return "";
    }
    if(ram_location != 0) {
        /* Have variable in memory at RAM location */
        instruction = std::string("LOAD MEM " +std::to_string(ram_location) + "\t#" + std::string(get_str()));
    } else {
        instruction = std::string("LOAD MEM " + std::string(get_str()));
    }
    return instruction;
}

bool Variable::get_is_pointer(void) const {
    return is_pointer;
}

void Variable::set_is_pointer(bool new_value) {
    is_pointer = new_value;
}

void Variable::set_ram_location(unsigned int new_ram_location) {
    ram_location = new_ram_location;
}

unsigned int Variable::get_ram_location(void) const {
    return ram_location;
}

/* Constant */

IToken *Constant::clone() const {
    return new Constant(*this);
}

eToken Constant::get_type(void) const {
    return eToken::Constant;
}

std::string_view Constant::assemble_instruction(void) const {
    instruction = std::string("PUSH " + std::string(get_str()));
    return instruction;
}

/* Keyword */

IToken *Keyword::clone() const {
    return new Keyword(*this);
}

eToken Keyword::get_type(void) const {
    return eToken::Keyword;
}

/* ITokenPredefined */

ITokenPredefined::ITokenPredefined() {
    IToken *token = reinterpret_cast<IToken *>(this); //TODO: figure a way to use dynamic_cast
    if(token == nullptr) {
        std::cerr << "Predefined token not in Itoken child" << std::endl;
        assert(false);
    }
    Tokenizer::add_operator(token);
}
