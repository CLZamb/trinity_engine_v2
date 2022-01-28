#include "game_drawings.hpp"

GameDrawings::GameDrawings() :
  m_no_message(this),
  m_start_or_quit(this),
  m_players_options(this),
  m_game_over(this),
  m_choose_color(this),
  m_top_menu(this),
  m_bottom_menu(this),
  m_player_1_won(this),
  m_player_2_won(this),
  p_current_state(&m_no_message) {}

std::string_view GameDrawings::get_drawing() {
  return p_current_state->get_drawing();
}

std::string_view GameDrawings::get_drawing(DrawingsState* state) {
  set_drawing(state);
  return get_drawing();
}

void GameDrawings::set_drawing(DrawingsState* state) {
  this->p_current_state = state;
}

DrawingsState* GameDrawings::get_play_or_quit() {
  return &m_start_or_quit;
}

DrawingsState* GameDrawings::get_players_options() {
  return &m_players_options;
}

DrawingsState* GameDrawings::get_game_over() {
  return &m_game_over;
}

DrawingsState* GameDrawings::get_choose_color() {
  return &m_choose_color;
}

DrawingsState* GameDrawings::get_no_message() {
  return &m_no_message;
}

DrawingsState* GameDrawings::get_top_menu() {
  return &m_top_menu;
}

DrawingsState* GameDrawings::get_bottom_menu() {
  return &m_bottom_menu;
}

DrawingsState* GameDrawings::get_player_1_won() {
  return &m_player_1_won;
}

DrawingsState* GameDrawings::get_player_2_won() {
  return &m_player_2_won;
}
