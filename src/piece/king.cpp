#include "king.h"

template<Color color>
King<color>::King() :
  Piece(color == BLACK ? bK : wK) {
    _init_moves();
}

template<Color color>
bool King<color>::is_legal_move(Move& m, BoardBitboard& board) {
  SquareIndices from = m.get_from();
  U64 to = ONE << m.get_to();
  const U64 free_squares = ~board.get_all_board_pieces();
  const U64 opponent =
    (color == BLACK) ? 
    board.get_all_side_pieces(WHITE) : board.get_all_side_pieces(BLACK);

  if (is_castle(m, free_squares)) {
    set_castle(m); 
    return true;
  }

  return m_attacks[from] & to & (free_squares | opponent);
}

template<Color color>
void  King<color>::set_castle(Move& m) {
  m.set_is_castle(true);
}

template<Color color>
bool King<color>::is_castle(Move m, U64 free_squares) {
  U64 from = ONE<< m.get_from();
  U64 to = ONE<< m.get_to();
  from = ::shift<EAST>(from);
  from |= ::shift<EAST>(from) & free_squares;
  if (from)
    from |= ::shift<EAST>(from) & free_squares;

  if (from & to) return true;

  from = ::shift<WEST>(from);
  from |= ::shift<WEST>(from) & free_squares;
  if (from)
    from |= ::shift<WEST>(from) & free_squares;

  return to & from;
}


