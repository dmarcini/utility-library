#include "scanner.hpp"

#include <sstream>
#include <iostream>
#include <limits>


namespace utility {

Scanner::Scanner(std::istream &istream, const std::string &delimiters)
    : istream_(istream)
{

}


Scanner::~Scanner()
{
    clear();
    reset();
}


void Scanner::clear()
{
    istream_.clear();
    istream_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void Scanner::reset()
{
    skip_pattern_ = std::nullopt;
}


void Scanner::skip(const std::string &pattern)
{
    skip_pattern_ = pattern;
}


bool Scanner::has_next()
{
    std::string token {};

    if (!buffor_.empty()) {
        return true;
    }

    if (!(istream_ >> token)) {
        return false;
    }

    buffor_.push(token);

    return true;
}


bool Scanner::has_next_line()
{
    if (buffor_.empty()) {
        std::string line;

        std::getline(istream_, line, '\n');

        buffor_.push(line);
    }

    return true;
}


bool Scanner::has_next_char()
{
    if (buffor_.empty()) {
        char c;

        if (!(istream_ >> c)) {
            return false;
        }

        buffor_.push(std::string(1, c));
    }

    return true;
}


bool Scanner::has_next_int()
{
    return has_next_number<int>([](const std::string& token) -> int {
        return std::stoi(token);
    });
}


bool Scanner::has_next_long()
{
    return has_next_number<long>([](const std::string& token) -> long {
        return std::stol(token);
    });
}


bool Scanner::has_next_unsigned_long()
{
    return has_next_number<unsigned long>([](const std::string& token)
                                          -> unsigned long {
        return std::stoul(token);
    });
}


bool Scanner::has_next_long_long()
{
    return has_next_number<long long>([](const std::string& token)
                                      -> long long {
        return std::stoll(token);
    });
}


bool Scanner::has_next_unsigned_long_long()
{
    return has_next_number<unsigned long long>([](const std::string& token)
                                               -> unsigned long long {
        return std::stoull(token);
    });
}


bool Scanner::has_next_float()
{
    return has_next_number<float>([](const std::string& token) -> float {
        return std::stof(token);
    });
}


bool Scanner::has_next_double()
{
    return has_next_number<double>([](const std::string& token) -> double {
        return std::stod(token);
    });
}


bool Scanner::has_next_long_double()
{
    return has_next_number<long double>([](const std::string& token)
                                        -> long double {
        return std::stold(token);
    });
}


std::string Scanner::next()
{
    std::string token {};

    if (!buffor_.empty()) {
        token = buffor_.front();

        size_t next_token_pos {buffor_.front().find_first_of(" \t")};

        if (next_token_pos != std::string::npos) {
            buffor_.front() = buffor_.front().substr(next_token_pos + 1);
        } else {
            buffor_.pop();
        }
    } else {
        istream_ >> token;
    }

    return token;
}


std::string Scanner::next_line()
{
    std::string line {};

    if (!buffor_.empty()) {
        line = buffor_.front();
        buffor_.pop();
    } else {
        if (istream_.peek() == '\n') {
            clear();
        }

        std::getline(istream_, line, '\n');
    }

    return line;
}


char Scanner::next_char()
{
    char c;

    if (!buffor_.empty()) {
        c = buffor_.front().front();
        buffor_.front().erase(0, 1);

        if (buffor_.front().empty()) {
            buffor_.pop();
        }
    } else {
        if (istream_.peek() == '\n') {
            clear();
        }

        istream_ >> c;
    }

    return c;
}


int Scanner::next_int()
{
    return std::stoi(next());
}


long Scanner::next_long()
{
    return std::stol(next());
}


unsigned long Scanner::next_unsigned_long()
{
    return std::stoul(next());
}


long long Scanner::next_long_long()
{
    return std::stoll(next());
}


unsigned long long Scanner::next_unsigned_long_long()
{
    return std::stoull(next());
}


float Scanner::next_float()
{
    return std::stof(next());
}


double Scanner::next_double()
{
    return std::stod(next());
}


long double Scanner::next_long_double()
{
    return std::stold(next());
}


template <typename T>
bool Scanner::has_next_number(std::function<T(const std::string&)> stonum)
{
    try {
        if (has_next()) {
            stonum(buffor_.front());
        } else {
            return false;
        }
    } catch(...) {
        buffor_.pop();

        return false;
    }

    return true;
}

} // namespace utility
