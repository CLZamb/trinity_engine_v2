#pragma once
#ifndef GAME_DRAWINGS_STATE_H
#define GAME_DRAWINGS_STATE_H

#include "drawings.hpp"

class GameDrawings;
class DrawingsState {
 public:
  explicit DrawingsState(GameDrawings* msg);
  const std::string_view get_drawing() { return m_string_drawing; }
 protected:
  GameDrawings* p_messages = nullptr;
  std::string_view m_string_drawing;
};

struct Play_or_quit : public DrawingsState {
  explicit Play_or_quit(GameDrawings* msg);
};

struct Players_options : public DrawingsState {
  explicit Players_options(GameDrawings* msg);
};

struct Game_over: public DrawingsState {
 public:
  explicit Game_over(GameDrawings* msg);
};

struct Choose_color : public DrawingsState {
 public:
  explicit Choose_color(GameDrawings* msg);
};

struct No_message : public DrawingsState {
 public:
  explicit No_message(GameDrawings* msg);
};

struct Top_Menu : public DrawingsState {
 public:
  explicit Top_Menu(GameDrawings* msg);
};

struct Bottom_Menu : public DrawingsState {
 public:
  explicit Bottom_Menu(GameDrawings* msg);
};

struct Player_one_won : public DrawingsState {
 public:
  explicit Player_one_won(GameDrawings* msg);
};

struct Player_two_won : public DrawingsState {
 public:
  explicit Player_two_won(GameDrawings* msg);
};

#endif /* GAME_DRAWINGS_STATE_H */
