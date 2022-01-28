#ifndef BOARD_WITH_INFO_H
#define BOARD_WITH_INFO_H

#include "board.h"
#include "info.h"
#include "savable.h"
#include "game/headers/game_turn_observer.h"

class BoardWithInfo : public GameTurnObserver {
 public:
  explicit BoardWithInfo();

  void make_move(Move m);
  void update_turn(GameTurn::players turn);
  void update_game_info(const string& info);
  bool is_checkmate();
  bool is_legal_move(std::shared_ptr<Player> turn, Move& m);
  std::shared_ptr<Player> get_turn();
  Displayable* get_board_drawing();
  Displayable* get_info_drawing();
  string get_fen();

 private:
  string get_turn_info(players turn);
  string get_str_moves(const Move& m);
  void save_move(const Move& m);
  void save_capture(const Move& m);

// r3k2r/8/8/8/8/8/8/R3K2R w - - 0 1
  Board m_board{"4k3/P6P/8/8/8/8/1p4p1/4K3"};
  Info m_info;
};

#endif /* BOARD_WITH_INFO_H */
