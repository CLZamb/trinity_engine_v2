#include "game_drawings_state.hpp"

DrawingsState::DrawingsState(GameDrawings* msg) : p_messages(msg) {}

Play_or_quit::Play_or_quit(GameDrawings* msg) : DrawingsState(msg) {
 m_string_drawing = p_play_or_quit_message;
}

Players_options::Players_options(GameDrawings* msg) : DrawingsState(msg) {
  m_string_drawing = p_options_players;
}

Game_over::Game_over(GameDrawings* msg) : DrawingsState(msg) {
  m_string_drawing = p_game_over;
}

Choose_color::Choose_color(GameDrawings* msg) : DrawingsState(msg) {
  m_string_drawing = p_choose_color_message;
}

No_message::No_message(GameDrawings* msg) : DrawingsState(msg) {
  m_string_drawing = p_no_message;
}

Top_Menu::Top_Menu(GameDrawings* msg) : DrawingsState(msg) {
  m_string_drawing = p_top_menu;
}

Bottom_Menu::Bottom_Menu(GameDrawings* msg) : DrawingsState(msg) {
  m_string_drawing = p_bottom_menu;
}


Player_one_won::Player_one_won(GameDrawings* msg) : DrawingsState(msg) {
  m_string_drawing = p_player_1_won;
}

Player_two_won::Player_two_won(GameDrawings* msg) : DrawingsState(msg) {
  m_string_drawing = p_player_2_won;
}


