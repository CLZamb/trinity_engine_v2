#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

template<Color color>
class Knight : public Piece{
  public:
    Knight();
    bool is_legal_move(Move&, BoardBitboard& board) override;

  private:
    constexpr U64 knight_mask(int sq) {
      U64 result = BLANK;
      U64 from_sq = ONE << sq;
      U64 shift = BLANK;

      shift = ::shift<SOUTH_SOUTH>(from_sq);
      shift = ::shift<WEST>(shift);
      if (shift & NOT_H_FILE)
        result |= shift & NOT_H_FILE;

      shift = ::shift<SOUTH_SOUTH>(from_sq);
      shift = ::shift<EAST>(shift);
      if (shift & NOT_A_FILE)
        result |= shift & NOT_A_FILE;

      shift = ::shift<SOUTH_WEST>(from_sq);
      shift = ::shift<WEST>(shift);
      if (shift & NOT_GH_FILE)
        result |= shift & NOT_GH_FILE;

      shift = ::shift<SOUTH_EAST>(from_sq);
      shift = ::shift<EAST>(shift);
      if (shift & NOT_AB_FILE)
        result |= shift & NOT_AB_FILE;

      shift = ::shift<NORTH_NORTH>(from_sq);
      shift = ::shift<EAST>(shift);
      if (shift & NOT_A_FILE)
        result |= shift & NOT_A_FILE;

      shift = ::shift<NORTH_NORTH>(from_sq);
      shift = ::shift<WEST>(shift);
      if (shift & NOT_H_FILE)
        result |= shift & NOT_H_FILE;

      shift = ::shift<NORTH_EAST>(from_sq);
      shift = ::shift<EAST>(shift);
      if (shift & NOT_AB_FILE)
        result |= shift & NOT_AB_FILE;

      shift = ::shift<NORTH_WEST>(from_sq);
      shift = ::shift<WEST>(shift);
      if (shift & NOT_GH_FILE)
        result |= shift & NOT_GH_FILE;

      return result;
    }

    constexpr void _init_moves() {
      for (int sq = 0; sq < utils::constant::ksquares; sq++) {
        m_attacks[sq] = knight_mask(sq);
      }
    }
};

#endif /* KNIGHT_H */
