#ifndef VIEW_H
#define VIEW_H

#include "../../board/headers/board_with_info.h"
#include "graphics/headers/game_drawings.hpp"
#include "graphics/headers/pane.h"
#include "window.h"
#include <iostream>
#include <string>
// #include"game_drawings.hpp.h"

using std::string;

class View {
public:
  View(string name);
  void print();

  static string Get_name();

protected:
  Window window_view;

private:
  static string name;
};

class BoardView : public View {
public:
  BoardView(BoardWithInfo *board) : View("Board") {
    window_view.add_displayable(board->get_board_drawing(),
                                Window::Middle_pane);
    window_view.add_displayable(board->get_info_drawing(), Window::Right_pane);
  }
};

class MenuView : public View, public Displayable {
public:
  MenuView(vector<string> opts) : View("Messages"), Displayable(3) {
    setup_view();

    p_top->set_content(
        {m_game_drawing.get_drawing(m_game_drawing.get_top_menu()).data()});
    p_options->set_content({format_options(opts)});
    p_bottom->set_content(
        {m_game_drawing.get_drawing(m_game_drawing.get_bottom_menu()).data()});
  }

private:
  size_t MaxCodeLength = 78;
  void draw() override {}
  void setup_view() {
    m_drawing.add_section(p_top);
    m_drawing.add_section(p_options);
    m_drawing.add_section(p_bottom);
    window_view.add_displayable(this, Window::Left_pane);
  }

  string format_options(vector<string> opts) {
    string str_menu_items;

    for (const auto &opt : opts) {
      str_menu_items = format_option(opt) + "\n " + str_menu_items;
    }

    str_menu_items += format_option("");
    return str_menu_items;
  }

  std::string format_option(const std::string &word) const {
    auto zerosNeeded_leftight = 25;
    auto zerosNeeded_right =
        (MaxCodeLength - zerosNeeded_leftight) - word.length();

    return "\t\t**" + std::string(zerosNeeded_leftight, ' ') + word +
           std::string(zerosNeeded_right, ' ') + "*";
  }

  shared_ptr<Section> p_top = std::make_shared<Section>("main", 1);
  shared_ptr<Section> p_options = std::make_shared<Section>("options", 1);
  shared_ptr<Section> p_bottom = std::make_shared<Section>("bottom", 1);
  GameDrawings m_game_drawing;
};

#endif /* VIEW_H */
