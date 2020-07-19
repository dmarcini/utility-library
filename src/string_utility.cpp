#include "string_utility.hpp"

#include <algorithm>
#include <regex>


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
    return src.find(c) != std::string::npos;
}


bool contains(const std::string &src, const char *regex)
{
    return contains(src, std::string(regex));
}


bool contains(const std::string &src, const std::string &regex)
{
    std::regex r(regex);
    std::smatch sm;

    if (std::regex_search(src, sm, r)) {
        return true;
    }

    return false;
}


std::string getline(std::istream &is)
{
    std::string line {};

    std::getline(is, line);

    return line;
}

}; //namespace utility
