#include <string>
#include <string_view>
#include <iostream>

#pragma once

class Token {
    private:
        std::string str;
    public:
        Token(std::string _str) : str(_str) {};
        virtual ~Token() = default;

        std::string_view get_str(void) const;
};