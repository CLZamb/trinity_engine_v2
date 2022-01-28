#ifndef VIEW_H
#define VIEW_H

#include "../../board/headers/board_with_info.h"
#include "graphics/headers/game_drawings.hpp"
#include "graphics/headers/pane.h"
#include "window.h"
#include <iostream>
#include <string>

using std::string;

class View {
public:
  View(string name);
  void print();

  static string Get_name();

protected:
  Window window_view;

private:
  static string _name;
};

class BoardView : public View {
public:
  BoardView(BoardWithInfo *board) : View("Board") {
    window_view.add_displayable(board->get_board_drawing(),
                                Window::Middle_pane);
    window_view.add_displayable(board->get_info_drawing(), Window::Left_pane);
  }
};

class MenuDisplay : public Displayable {
public:
  MenuDisplay(string opts) : Displayable(3) {
    m_drawing.add_section(p_top);
    m_drawing.add_section(p_options);
    m_drawing.add_section(p_bottom);
    p_top->set_content({m_top_drawing.data()});
    p_options->set_content({opts});
    p_bottom->set_content({m_bottom_drawing.data()});
  }

  void draw() override {}

private:
  GameDrawings m_menu_drawing;
  shared_ptr<Section> p_top = std::make_shared<Section>("top");
  shared_ptr<Section> p_options = std::make_shared<Section>("options");
  shared_ptr<Section> p_bottom = std::make_shared<Section>("bottom");

  std::string_view m_top_drawing = m_menu_drawing.get_top_menu()->get_drawing();
  std::string_view m_bottom_drawing =
      m_menu_drawing.get_bottom_menu()->get_drawing();
};

class MenuView : public View {
public:
  MenuView(vector<string> opts)
      : View("Menu"), m_display(format_options(opts)) {
    window_view.add_displayable(&m_display, Window::Left_pane);
  }

private:
  static constexpr size_t MaxCodeLength = 78;
  static constexpr size_t Left_space_length = 25;

  string format_options(vector<string> opts) {
    string str_menu_items;

    for (const auto &opt : opts) {
      str_menu_items = format_option(opt) + "\n " + str_menu_items;
    }

    str_menu_items += format_option("");
    return str_menu_items;
  }

  std::string format_option(const std::string &word) const {
    auto zerosNeeded_right =
        (MaxCodeLength - Left_space_length) - word.length();

    return "\t\t**" + std::string(Left_space_length, ' ') + word +
           std::string(zerosNeeded_right, ' ') + "*";
  }

  MenuDisplay m_display;
};

class WinnerDisplay : public Displayable {
public:
  WinnerDisplay(bool has_player_1_won) : Displayable(1) {
    m_drawing.add_section(p_main);
    p_main->set_content(
        {has_player_1_won
             ? m_menu_drawing.get_player_1_won()->get_drawing().data()
             : m_menu_drawing.get_player_2_won()->get_drawing().data()});
  }

  void draw() override {}

private:
  GameDrawings m_menu_drawing;
  shared_ptr<Section> p_main = std::make_shared<Section>("main");
};

class WinnerView : public View {
public:
  WinnerView(bool has_player_1_won)
      : View("Winner"), m_display(has_player_1_won) {
    window_view.add_displayable(&m_display, Window::Middle_pane);
  }

private:
  WinnerDisplay m_display;
};

#endif /* VIEW_H */
