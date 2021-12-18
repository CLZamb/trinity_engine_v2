#ifndef MENU_H
#define MENU_H

#include "board/headers/utils.h"
#include "graphics/headers/game_drawings_state.hpp"
#include "graphics/headers/view.h"
#include "options.h"
#include "player/headers/player.h"


template<typename T>
class Menu {
public:
  Menu() {}
  Menu(MenuList<T> opts) : opts(opts) {}
  virtual ~Menu() {}
  void print_menu()  {
    view.print();
  }
  
  T select_option() {
    return select_menu_item().opt;
  }
  
  void print_play_or_quit() {
    print(view.get_play_or_quit_menu());
  }

  void print_players_options() {
    print(view.get_play_players_options_menu());
  }

  MenuItem<T>& select_menu_item() {
    cout << "\t\tchoose one of the options:\n\t\t>> ";

    int input = -1;
    bool valid_option = false;

    while (!valid_option) {
      cin >> input;
      valid_option = opts.check_valid_option(input);

      if (!valid_option) {
        cout << "invalid option try again!" << endl;
        cin.clear();
        cin.ignore();
      }
    }

    cin.clear();
    cin.ignore();
    return opts.find_at_index(input);
  }

private:
  void print(DrawingsState* state) {
    view.update_menu_view(state);
    view.print();
  }

  MenuList<T> opts;
  MenuView view;
};

#endif /* MENU_H */ 
