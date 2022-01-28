#ifndef BOARDBITBOARD_H
#define BOARDBITBOARD_H
#include "../../common/headers/defs.h"
#include "../../common/headers/bit_utilities.h"

class BoardBitboard {
public:
  BoardBitboard() {}
  virtual ~BoardBitboard() {}
  void move(bool is_black, SquareIndices from, SquareIndices to) {
    clear_bit_at_player_pieces(is_black, from);
    set_bit_at_player_pieces(is_black, to);
  }

  U64 get_all_side_pieces(bool is_black) const {
    return (is_black)? m_all_b_pieces : m_all_w_pieces;
  }

  U64 get_all_board_pieces() const {
    return m_occupied;
  }

  void set_bit_at_player_pieces(bool is_black, SquareIndices pos) {
    bitUtility::set_bit(is_black ? &m_all_b_pieces : &m_all_w_pieces, pos);
    bitUtility::set_bit(&m_occupied, pos);
  }

  void clear_bit_at_player_pieces(bool is_black, SquareIndices pos) {
    bitUtility::clear_bit(is_black ? &m_all_b_pieces : &m_all_w_pieces, pos);
    bitUtility::clear_bit(&m_occupied, pos);
  }

  void set_en_passant(SquareIndices pos, Color c) {
    if (c == BLACK)
      bitUtility::set_bit(&m_en_passant_black, pos);
    else // c = white
      bitUtility::set_bit(&m_en_passant_white, pos);
  }

  const U64& get_en_passant(Color c) {
    return (c == BLACK) ? m_en_passant_black : m_en_passant_white;
  }

  void set_en_castle(SquareIndices pos, Color c) {
    if (c == BLACK)
      bitUtility::set_bit(&m_castle_black, pos);
    else // c = white
      bitUtility::set_bit(&m_castle_white, pos);
  }

  const U64& get_castle(Color c) {
    return (c == BLACK) ? m_castle_black : m_castle_white;
  }

  void remove_en_passant(SquareIndices pos, Color c) {
    if (c == BLACK)
      bitUtility::clear_bit(&m_en_passant_black, pos);
    else // c = white
      bitUtility::clear_bit(&m_en_passant_white, pos);
  }

private:
  U64 m_en_passant_black = BLANK;
  U64 m_en_passant_white = BLANK;
  U64 m_castle_black = BLANK;
  U64 m_castle_white = BLANK;
  U64 m_all_w_pieces = BLANK;
  U64 m_all_b_pieces = BLANK;
  U64 m_occupied = BLANK;
};

#endif /* BOARDBITBOARD_H */
