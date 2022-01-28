#ifndef KING_H
#define KING_H

#include "piece.h"

template<Color color>
class King : public Piece {
  public:
    King();
    bool is_legal_move(Move&, BoardBitboard& board) override;
  private:
    U64 king_mask(int sq) {
      U64 king_mask = 0ULL;
      U64 from_sq = ONE << sq;

      king_mask |= ::shift<NORTH>(from_sq);
      king_mask |= ::shift<SOUTH>(from_sq);
      king_mask |= ::shift<EAST>(from_sq);
      king_mask |= ::shift<WEST>(from_sq);
      king_mask |= ::shift<NORTH_EAST>(from_sq);
      king_mask |= ::shift<NORTH_WEST>(from_sq);
      king_mask |= ::shift<SOUTH_EAST>(from_sq);
      king_mask |= ::shift<SOUTH_WEST>(from_sq);
      return king_mask;
    }

    bool is_castle(Move m, U64 free_squares);
    void set_castle(Move& m);

    void _init_moves() {
      for (int sq = 0; sq < utils::constant::ksquares; sq++) {
        m_attacks[sq] = king_mask(sq);
      }
    }
};

#endif /* KING_H */
