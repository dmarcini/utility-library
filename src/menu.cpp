#include "menu.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <exception>
#include <functional>

#include "scanner.hpp"


namespace utility {

Menu::Menu(std::string_view title, const std::vector<Item> &items)
    : title_(title), items_(items) {};


void Menu::show()
{
    show(*this);
}


std::string& Menu::title()
{
    return title_;
}


const std::string& Menu::title() const
{
    return title_;
}


auto Menu::items() -> std::vector<Item>&
{
    return items_;
}


auto Menu::items() const -> const std::vector<Item>&
{
    return items_;
}


auto Menu::item(const size_t idx) -> Item&
{
    return items_.at(idx);
}


auto Menu::item(const size_t idx) const -> const Item&
{
    return items_.at(idx);
}


void Menu::append(const Item &item)
{
    items_.emplace_back(item);
}


void Menu::insert(const size_t idx, const Item &item)
{
    if (idx < items_.size()) {
        items_.insert(items_.begin() + idx, item);
    }
}


void Menu::erase(const size_t idx)
{
    if (idx < items_.size()) {
        items_.erase(items_.begin() + idx);
    }
}


void Menu::show(const Menu &menu)
{
    static Scanner scanner(std::cin);

    auto show = [items_num {items_.size()}](const Menu& menu) {
        std::cout << menu.title_ << "\n\n";

        for (size_t i = 0; i < items_num; ++i) {
            std::cout << i + 1 << ") " << menu.items_[i].name << "\n";
        }

        std::cout << "0) Exit menu\n\n";
        std::cout << "Enter menu option number (0-" << items_num << "): ";

        while (!scanner.has_next_int()) {
            std::cout << "Input must be number! Please enter again: ";
        }

        return scanner.next_int();
    };

    for (int option {0}; (option = show(menu)) > 0;) {
        if (option < 0 || option > static_cast<int>(items_.size())) {
            std::cout << "\nNumber must be in range: <"
                      << 0 << ", " << items_.size() << ">! "
                      << "Please enter again:\n";
            continue;
        }

        const auto &item = menu.items_[option - 1];

        if (std::holds_alternative<FuncPtr>(item.content)) {
            std::get<FuncPtr>(item.content)();
        } else {
            std::get<Menu*>(item.content)->show();
        }
    }
}

} // namespace utility
