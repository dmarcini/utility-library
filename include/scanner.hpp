#ifndef SCANNER_HPP_
#define SCANNER_HPP_

#include <sstream>
#include <string>
#include <optional>
#include <queue>
#include <functional>
#include <locale>


namespace utility {

class Scanner final
{
public:
    Scanner(std::istream &istream, const std::string &delimiters = "");
    ~Scanner();

    Scanner(const Scanner&) = delete;
    Scanner& operator=(const Scanner&) = delete;
    Scanner(Scanner&&) = delete;
    Scanner&& operator=(Scanner&&) = delete;

    void clear();
    void reset();

    void set_delimiters(const std::string &delimiters);
    void set_delimiters(char delimiter);
    void append_delimiters(const std::string &delimiters);
    void append_delimiters(char delimiter);
    void remove_delimiters(const std::string &delimiters);
    void remove_delimiters(char delimiter);
    void reset_delimiters();
    std::string get_delimiters() const;

    void skip(const std::string &pattern);

    bool has_next();
    bool has_next_line();
    bool has_next_char();
    bool has_next_int();
    bool has_next_long();
    bool has_next_unsigned_long();
    bool has_next_long_long();
    bool has_next_unsigned_long_long();
    bool has_next_float();
    bool has_next_double();
    bool has_next_long_double();

    std::string next();
    std::string next_line();
    char next_char();
    int next_int();
    long next_long();
    unsigned long next_unsigned_long();
    long long next_long_long();
    unsigned long long next_unsigned_long_long();
    float next_float();
    double next_double();
    long double next_long_double();
private:
    struct Delimiters : std::ctype<char> {
    public:
        enum class Option
        {
            Set,
            Append,
            Remove,
            Reset
        };

        Delimiters(const std::string &delimiters, Option option,
                   std::size_t refs = 0);

        static mask* make_table(const std::string &delimiters,
                                Option option);

        static void set_delimiters(const std::string &delimiters);
        static void append_delimiters(const std::string &delimiters);
        static void remove_delimiters(const std::string &delimiters);
        static void reset_delimiters();
        static std::string get_delimiters();
    private:
        static const mask *classic_table_;
        static const size_t table_size_;

        static std::vector<mask> locale_table_;
        static std::vector<mask> default_table_;

        static std::string delimiters_;
        static constexpr std::string_view default_delimiters_ {" \t\f\v\r"};
    };

    template <typename T>
    bool has_next_number(std::function<T(const std::string&)> stonum);

    std::istream &istream_;

    std::queue<std::string> buffor_ {};

    std::optional<std::string> skip_pattern_ {std::nullopt};
};

} // namespace utility;

#endif // SCANNER_HPP_2222222
