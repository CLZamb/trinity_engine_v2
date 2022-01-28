#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "../../general/headers/bitUtilities.hpp"
#include "../../general/headers/utils.h"

class Piece {
 public:
  explicit Piece(Piecetype pct, U64 bb);
  virtual ~Piece();
  void clear_bit(SquareIndices pos);
  void set_bit(SquareIndices pos);
  void make_move(SquareIndices from, SquareIndices to);
  void clear_bitboard();
  void set_material_score(Piecetype);
  int get_material_score();
  bool is_black();
  Piecetype get_type_and_color();
  U64 get_bitboard();

 private:
  bool black = false;
  int m_material_score = 0;
  U64 m_bitboard = BLANK;
  Piecetype m_type = EMPTY;
};

#endif /* PIECE_H */
