#ifndef MENU_HPP_
#define MENU_HPP_

#include <string>
#include <vector>
#include <functional>
#include <variant>
#include <memory>


namespace utility {

class Menu final
{
public:
    using FuncPtr = std::function<void(void)>;

    struct Item {
        std::string name {};
        std::variant<FuncPtr, Menu*> content {nullptr};
    };

    Menu() = default;
    Menu(std::string_view title, const std::vector<Item>& items = {});

    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
    Menu(Menu&&) = delete;
    Menu& operator=(Menu&&) = delete;

    ~Menu() = default;

    void show();

    std::string& title();
    const std::string& title() const;

    std::vector<Item>& items();
    const std::vector<Item>& items() const;

    Item& item(size_t idx);
    const Item& item(size_t idx) const;

    void append(const Item &item);
    void insert(size_t idx, const Item &item);
    void erase(size_t idx);
private:
    void show(const Menu &menu);

    std::string title_ {};
    std::vector<Item> items_ {};
};

} // namespace utility

#endif // MENU_HPP_
