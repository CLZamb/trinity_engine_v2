#ifndef QUEEN_H
#define QUEEN_H 

#include "piece.h"
#include "magic_bitboard.h"
#include "sliding_moves.hpp"

template<Color color>
class Queen : public Piece {
public:
  explicit Queen(IMagicBitboardAttackType& m_bb);
  bool is_legal_move(Move&, BoardBitboard& board) override;

private:
  SlidingMoves<color> queen_moves;
};

#endif /* ifndef QUEEN_H */
