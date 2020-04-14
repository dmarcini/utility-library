#include "string_utility.hpp"

#include <algorithm>


namespace utility {

void remove_chars(std::string &src, char chars_to_remove)
{
    remove_chars(src, std::string(1, chars_to_remove));
}


void remove_chars(std::string &src, const char *chars_to_remove)
{
    remove_chars(src, std::string(chars_to_remove));
}


void remove_chars(std::string &src, const std::string &chars_to_remove)
{
    src.erase(std::remove_if(src.begin(), src.end(), [&](char c) {
        return contains(chars_to_remove, c);
    }), src.end());
}


bool contains(const std::string &src, const char c)
{
    return contains(src, std::string(1, c));
}


bool contains(const std::string &src, const char *str)
{
    return contains(src, std::string(str));
}


bool contains(const std::string &src, const std::string &str)
{
    return src.find(str) != std::string::npos;
}

}; //namespace utility
