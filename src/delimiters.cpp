#include "scanner.hpp"

#include <locale>
#include <string>
#include <cctype>

#include "string_utility.hpp"


namespace utility {

using mask = std::ctype_base::mask;


const mask *Scanner::Delimiters::classic_table_ {ctype<char>::classic_table()};
const size_t Scanner::Delimiters::table_size_ {ctype<char>::table_size};

std::string Scanner::Delimiters::delimiters_ {default_delimiters_};


std::vector<mask> Scanner::Delimiters::locale_table_(classic_table_,
                                                     classic_table_ + table_size_);
std::vector<mask> Scanner::Delimiters::default_table_(locale_table_);


Scanner::Delimiters::Delimiters(const std::string &delimiters, Option option,
                                std::size_t refs)
    : ctype(make_table(delimiters, option), false, refs) {}


mask* Scanner::Delimiters::make_table(const std::string &delimiters,
                                      Option option)
{
    switch (option) {
        case Option::Set:
            set_delimiters(delimiters);
            break;
        case Option::Append:
            append_delimiters(delimiters);
            break;
        case Option::Remove:
            remove_delimiters(delimiters);
            break;
        case Option::Reset:
            reset_delimiters();
            break;
    }

    return &locale_table_[0];
}


void Scanner::Delimiters::set_delimiters(const std::string &delimiters)
{
    remove_delimiters(delimiters_);
    append_delimiters(delimiters);
}


void Scanner::Delimiters::append_delimiters(const std::string &delimiters)
{
    for (char delimiter : delimiters) {
        locale_table_[delimiter] |= space;
    }

    delimiters_ += delimiters;
}


void Scanner::Delimiters::remove_delimiters(const std::string &delimiters)
{
    for (char delimiter : delimiters) {
        locale_table_[delimiter] &= ~space;
    }

    remove_chars(delimiters_, delimiters);
}


void Scanner::Delimiters::reset_delimiters()
{
    locale_table_ = default_table_;
    delimiters_ = default_delimiters_;
}


std::string Scanner::Delimiters::get_delimiters()
{
    return delimiters_;
}

}; // namespace utility
