#include "headers/game_drawings_state.hpp"

DrawingsState::DrawingsState(GameDrawings* msg) : p_messages(msg) {}
DrawingsState::~DrawingsState() {}

Play_or_quit::Play_or_quit(GameDrawings* msg) : DrawingsState(msg) {
  p_message = p_play_or_quit_message;
}

Players_options::Players_options(GameDrawings* msg) : DrawingsState(msg) {
  p_message = p_options_players;
}

Game_over::Game_over(GameDrawings* msg) : DrawingsState(msg) {
  p_message = p_game_over;
}

Choose_color::Choose_color(GameDrawings* msg) : DrawingsState(msg) {
  p_message = p_choose_color_message;
}

No_message::No_message(GameDrawings* msg) : DrawingsState(msg) {
  p_message = p_no_message;
}
