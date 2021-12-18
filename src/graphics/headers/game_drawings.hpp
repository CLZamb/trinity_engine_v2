#pragma once
#ifndef GAME_DRAWINGS_H
#define GAME_DRAWINGS_H

#include"Idisplay.h"
#include"game_drawings_state.hpp"
#include"section.h"

enum Msg : int {
  no_message,
  welcome,
  chooseColor,
  chooseStartOption,
  gameOver
};

class GameDrawings {
 public:
    GameDrawings();
    ~GameDrawings();
    void set_drawing(DrawingsState* message_state);
    std::string_view get_drawing();
    std::string_view get_drawing(DrawingsState* message_state);

    DrawingsState* get_play_or_quit();
    DrawingsState* get_players_options();
    DrawingsState* get_game_over();
    DrawingsState* get_choose_color();
    DrawingsState* get_no_message();
    DrawingsState* get_top_menu();
    DrawingsState* get_bottom_menu();

 private:
    No_message m_no_message;
    Play_or_quit m_start_or_quit;
    Players_options m_players_options;
    Game_over m_game_over;
    Choose_color m_choose_color;
    Top_Menu m_top_menu;
    Bottom_Menu m_bottom_menu;
    DrawingsState* p_current_state;
};

#endif /*  */
