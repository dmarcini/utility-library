# Utility Libray

A set of objects and functions that support writing code.

---
## Description

The library consists of 5 modules:
* menu (menu.hpp header)
* rand (rand.hpp header)
* scanner (scanner.hpp header)
* string utility (string_utility.hpp header)
* timer (timer.hpp header)

All of them provide specific functions and methods described below.

### Menu module

This module contains a Menu class for creating a user menu.

Constructors:
* <strong>Menu() = default</strong>
* <strong>Menu(std::string_view title, const std::vector<Item>& items = {})</strong>
* <strong>Menu(const Menu&) = delete</strong>
* <strong>Menu& operator=(const Menu&) = delete</strong>
* <strong>Menu(Menu&&) = delete</strong>
* <strong>Menu& operator=(Menu&&) = delete</strong>

Methods:
* <strong>void show()</strong>
* <strong>const std::string& title() const</strong>
* <strong>const std::vector<Item>& items() const</strong>
* <strong>const Item& item(size_t idx) const</strong>
* <strong>void append(const Item &item)</strong>
* <strong>void insert(size_t idx, const Item &item)</strong>
* <strong>void erase(size_t idx)</strong>

Example of usage:
```
void func1() {}
void func2(int x, int y) {}

utility::Menu menu("Menu Title"); // create menu with title "Menu Title"

menu.append({"Option 1", func1}); // add option as function without parameters
menu.insert(0, {"Option 2", []() { // insert option as function
    func2(2, 5);                             // with parameters (use lamda)
}});                                         

menu.erase(1); // remove "Option 1";

menu.show(); // display menu
```

### Rand module

This module contains a template rand function for generate pseudo random values.

* <strong>T rand(std::int_fast64_t min = 0, std::int_fast64_t max = std::numeric_limits<T>::max())</strong> - 
  generate a pseudo random value from given range.

Example of usage:
```
using utility;

int x = rand(50, 100); // generate random integer value from range <50, 100>
auto y = rand<unsigned>(); // generate random unsigned value from range<0, max>
```

### Scanner module

This module contains a Scanner class which allows
you to retrieve correct data from the user.

Constructors:
* <strong>Scanner(std::istream &istream, const std::string &delimiters = "")</strong>
* <strong>Scanner(const Scanner&) = delete</strong>
* <strong>Scanner& operator=(const Scanner&) = delete</strong>
* <strong>Scanner(Scanner&&) = delete</strong>
* <strong>Scanner&& operator=(Scanner&&) = delete</strong>

Methods:
* <strong>void clear()</strong> - clear input stream
* <strong>void reset()</strong> - reset user settings like delimiters
* <strong>void set_delimiters(const std::string &delimiters)</strong>
* <strong>void set_delimiters(char delimiter)</strong>
* <strong>void append_delimiters(const std::string &delimiters)</strong>
* <strong>void append_delimiters(char delimiter)</strong>
* <strong>void remove_delimiters(const std::string &delimiters)</strong>
* <strong>void remove_delimiters(char delimiter)</strong>
* <strong>void reset_delimiters()</strong>
* <strong>std::string get_delimiters() const</strong>
* <strong>void skip(const std::string &pattern)</strong>
* <strong>bool has_next()</strong>
* <strong>bool has_next_line()</strong>
* <strong>bool has_next_char()</strong>
* <strong>bool has_next_int()</strong>
* <strong>bool has_next_long()</strong>
* <strong>bool has_next_unsigned_long()</strong>
* <strong>bool has_next_unsigned_long_long()</strong>
* <strong>bool has_next_float()</strong>
* <strong>bool has_next_double()</strong>
* <strong>bool has_next_long_double()</strong>
* <strong>std::string next()</strong>
* <strong>std::string next_line()</strong>
* <strong>char next_char()</strong>
* <strong>int next_int()</strong>
* <strong>long next_long()</strong></strong>
* <strong>unsigned long next_unsigned_long()</strong>
* <strong>long long next_long_long()</strong>
* <strong>unsigned long long next_unsigned_long_long()</strong>
* <strong>float next_float()</strong>
* <strong>double next_double()</strong>
* <strong>long double next_long_double()</strong>

Example of usage:
```
utility::Scanner scanner(std::cin);

while (!scanner.has_next_int()) { // repeat loop while input is invalid
    std::cout << "Incorrect input. Please enter the interger!";
}

int num = scaner.next_int(); // return a valid value entered by the user
```

### String utility module

This module contains normal and template functions for performing operations on strings.

* <strong>void remove_chars(std::string &src, char chars_to_remove)</strong>
* <strong>void remove_chars(std::string &src, const char *chars_to_remove)</strong>
* <strong>void remove_chars(std::string &src, const std::string &chars_to_remove)</strong>
* <strong>bool contains(const std::string &src, char c)</strong>
* <strong>bool contains(const std::string &src, const char *regex)</strong>
* <strong>bool contains(const std::string &src, const std::string &regex)</strong>
* <strong>std::string getline(std::istream &is)</strong>
* <strong>std::string to_string(T &value)</strong>
* <strong>void from_string(const std::string &string, char delim, std::vector&lt;T&gt; &vec)</strong>

Example of usage:
```
using utility;

std::string str = "Hello World!";

remove_chars(str, '!'); // str == "Hello World"
remove_chars(str, " World"); // str == "Hello"

contains(str, "ell"); // true
contains(str, "World); // false

str = getline(std::cin); // read line from input stream and return it
str = to_string(5); // str == "5"

std::vector<int> nums;
str = "1 2 3 4 5";
from_string(str, ' ', nums); // nums == {1, 2, 3, 4, 5}
```

### Timer module

This module contains a Timer class for measuring a time.

Constructors:
* <strong>Timer()</strong> - start measuring time
* <strong>Timer(const Timer&) = delete</strong>
* <strong>Timer& operator=(const Timer&) = delete</strong>
* <strong>Timer(Timer&&) = delete</strong>
* <strong>Timer& operator=(Timer&&)</strong>

Methods:
* <strong>void reset()</strong> - reset timer to current time.
* <strong>TRep elapsed() const</strong> - return subtract between current time and
  timer start time. TRep is template parameter: time representation type (default = double)

Example of usage:
```
utility::Timer timer; // start measuring time t1;

int x = 5;
int y = 10;

auto a = timer.elapsed(); // get current time t2 and return result = t1 - t2
auto b = timer.elapsed(); // get current time t3 and return result = t1 - t3
```
---
## Technology
* C++17
* cmake
* make
---

## Requirements
* Operation system: Windows, Linux, macOS
* C++17 compiler
* cmake tool installed
* make tool installed
---

## Building & Installing
Example for Linux system.
```
git clone library-url
cd path-to-clone-library
mkdir build
cd build
cmake ..
sudo make install
```

## Usage
To use the library you have to include appropriate headers e.g.:
* #include "menu.hpp" to use Menu class
* #include "scanner.hpp" to use Scanner class
* #include "string_utility.hpp" to use string utility funcrions

All classes and funtions are placed in <em>utility</em> namespace.
<br>
For example to create a Timer object you have to type:
```
utility::Timer timer;
```
