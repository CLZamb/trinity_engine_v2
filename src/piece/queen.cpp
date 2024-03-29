#include "queen.h"

template<Color color>
Queen<color>::Queen(IMagicBitboardAttackType& m_bb) :
  Piece(color == BLACK ? bQ : wQ), queen_moves(m_bb) {}

template<Color color>
bool Queen<color>::is_legal_move(Move& m, BoardBitboard& board) {
  return queen_moves.get_sliding_attacks(m, board);
}
