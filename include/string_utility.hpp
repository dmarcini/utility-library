#ifndef STRING_UTILITY__HPP_
#define STRING_UTILITY_HPP_

#include <string>


namespace utility {

void remove_chars(std::string &src, char chars_to_remove);
void remove_chars(std::string &src, const char *chars_to_remove);
void remove_chars(std::string &src, const std::string &chars_to_remove);

bool contains(const std::string &src, char c);
bool contains(const std::string &src, const char *str);
bool contains(const std::string &src, const std::string &str);

}; // namespace utility

#endif // STRING_UTILITY_HPP_
