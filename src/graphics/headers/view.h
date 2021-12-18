#ifndef VIEW_H
#define VIEW_H

#include<string>
#include<iostream>
#include"../../board/headers/board_with_info.h"
#include"graphics/headers/game_drawings.hpp"
#include"graphics/headers/pane.h"
#include"window.h"
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
    BoardView(BoardWithInfo * board) : View("Board") {
      window_view.add_pane(board->get_board_drawing(), Window::Middle_pane);
      window_view.add_pane(board->get_info_drawing(), Window::Right_pane);
    }
};

class MenuView : public View , public Displayable {
  public: 
    MenuView() : View("Messages"), Displayable(3) {
      m_drawing.add_section(p_main);
      window_view.add_pane(this, Window::Left_pane);
    }

    void update_menu_view(DrawingsState* state) {
      m_game_drawing.set_drawing(state);
    }

    DrawingsState* get_play_or_quit_menu() {
      return m_game_drawing.get_play_or_quit();
    }

    DrawingsState* get_play_players_options_menu() {
      return m_game_drawing.get_players_options();
    }

    void draw() {
      m_drawing.fill(m_game_drawing.get_drawing().data());
    }

  private:
    shared_ptr<Section> p_main = std::make_shared<Section>("main", 1);
    GameDrawings m_game_drawing;
};
 
#endif /* VIEW_H */
