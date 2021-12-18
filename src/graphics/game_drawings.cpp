#include "headers/game_drawings.hpp"

GameDrawings::GameDrawings() :
  m_no_message(this),
  m_start_or_quit(this),
  m_players_options(this),
  m_game_over(this),
  m_choose_color(this),
  p_current_state(&m_no_message) {}

GameDrawings::~GameDrawings() {}

std::string_view GameDrawings::get_drawing() {
  return p_current_state->get_message();
}

void GameDrawings::set_drawing(DrawingsState* state) {
  this->p_current_state = state;
}
//
// void GameDrawings::set_drawing(DrawingsState* state, vector<string> options) {
//   this->p_current_state = state;
//
//   p_options = std::make_shared<Section>("options", options.size());
//
//   string temp = "";
//   for (auto& i : options) {
//
//     temp = 
//      "\t\t**                          "+ i +"                                     *\n ";
//     i = temp;
//   }
//   p_options->set_content(&options);
//   p_main->set_content({p_current_state->get_message().data()});
//   m_drawing.add_section(p_options);
// }
//
// std::string GameDrawings::space_pad(const std::string &word) const {
//   const size_t max_lenght = 80;
//   auto space_Needed_right = (80 - word.length());
//   auto space_Needed_left = (80 - word.length());
//   return word + std::string(zerosNeeded, '0');
// }
//
// void GameDrawings::draw() {
//   // m_drawing.fill(p_current_state->get_message());
//   // if (p_options != nullptr) {
//   //   m_drawing.set_content(p_options.get());
//   // }
//   // m_drawing.fill(p_current_state->get_message());
// }

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
