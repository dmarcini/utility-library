#ifndef STRING_UTILITY_HPP_
#define STRING_UTILITY_HPP_

#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>


namespace utility {

void remove_chars(std::string &src, char chars_to_remove);
void remove_chars(std::string &src, const char *chars_to_remove);
void remove_chars(std::string &src, const std::string &chars_to_remove);

bool contains(const std::string &src, char c);
bool contains(const std::string &src, const char *regex);
bool contains(const std::string &src, const std::string &regex);

std::string getline(std::istream &is);

template<typename T>
std::string to_string(T &value);

template<typename T>
void from_string(const std::string &string, char delim, std::vector<T> &vec);


template<typename T>
std::string to_string(const T &value)
{
    std::ostringstream oss;

    if (!(oss << value)) {
        oss.clear();

        throw std::invalid_argument("can't be convert to string");
    }

    return oss.str();
}


template<typename T>
void from_string(const std::string &string, const char delim,
                 std::vector<T> &vec)
{
    std::istringstream iss(string);

    for (T value; iss >> value;) {
        vec.emplace_back(value);

        if (iss.peek() == delim) {
            iss.ignore();
        }
    }
}

}; // namespace utility

#endif // STRING_UTILITY_HPP_
