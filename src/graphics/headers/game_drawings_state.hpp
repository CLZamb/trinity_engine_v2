#pragma once
#ifndef GAME_DRAWINGS_STATE_H
#define GAME_DRAWINGS_STATE_H

#include "drawings.hpp"

class GameDrawings;
class DrawingsState {
 public:
  explicit DrawingsState(GameDrawings* msg);
  virtual ~DrawingsState();
  const std::string_view get_message() { return p_message; }
 protected:
  GameDrawings* p_messages = nullptr;
  std::string_view p_message;
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


#endif /* GAME_DRAWINGS_STATE_H */
