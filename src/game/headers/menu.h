#ifndef MENU_H
#define MENU_H

#include "common/headers/utils.h"
#include "graphics/headers/game_drawings_state.hpp"
#include "graphics/headers/view.h"
#include "options.h"
#include "player/headers/player.h"

template <typename T> class Menu {
public:
  Menu() {}
  Menu(MenuList<T> opts) : m_opts(opts), view(add_options_to_view(opts)) {}

  T select_option() { return select_menu_item().opt; }

  void print_menu() { view.print(); }

  void set_menu_drawing(string str) { str_view = str; }

  MenuItem<T> &select_menu_item() {
    cout << "\t\t\tchoose one of the options:\n";

    char input = ' ';
    bool valid_option = false;

    while (!valid_option) {
      cout << "\t\t\t>> ";
      cin >> input;
      valid_option = m_opts.check_valid_option(input);

      if (!valid_option) {
        cout << "\n\t\t\tinvalid option try again!" << endl;
        cin.clear();
        cin.ignore();
      }
    }

    cin.clear();
    cin.ignore();
    return m_opts.find_at_index(input);
  }

private:
  vector<string> add_options_to_view(MenuList<T> &opts) {
    vector<string> options;
    string str_menu_item;
    for (const auto &menuItem : opts) {
      MenuItem<T> item = menuItem.second;
      str_menu_item = std::string{item.option_key} + ". " + item.name;
      options.push_back(str_menu_item);
    }
    return options;
  }

  MenuList<T> m_opts;
  MenuView view;
  string str_view;
};

#endif /* MENU_H */
