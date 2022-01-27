#ifndef BISHOP_H
#define BISHOP_H 

#include "piece.h"
#include "magic_bitboard.h"
#include "sliding_moves.hpp"

template<Color color>
class Bishop : public Piece {
public:
  explicit Bishop(IMagicBitboardAttackType& m_bb);
  bool is_legal_move(Move&, BoardBitboard& board) override;

private:
  SlidingMoves<color> bishop_moves;
};

#endif /* ifndef BISHOP_H */

