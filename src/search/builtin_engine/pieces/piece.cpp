#include "piece.h"

Piece::Piece(Piecetype pct, U64 bb) :
  black(utils::check::is_black_piece(pct)), m_bitboard(bb), m_type(pct) {
  set_material_score(pct);
}

Piece::~Piece() {}

void Piece::set_material_score(Piecetype pct) {
  m_material_score = utils::constant::piece_material_score[pct];
}

U64 Piece::get_bitboard() { return m_bitboard; }
Piecetype Piece::get_type_and_color() { return m_type; }
bool Piece::is_black() { return black; }
void Piece::clear_bit(SquareIndices pos) {
  bitUtility::clear_bit(&m_bitboard, pos);
}
void Piece::set_bit(SquareIndices pos) {
  bitUtility::set_bit(&m_bitboard, pos);
}
void Piece::make_move(SquareIndices from, SquareIndices to) {
  clear_bit(from); set_bit(to);
}
void Piece::clear_bitboard() { m_bitboard = BLANK; }
int Piece::get_material_score() {
  return (bitUtility::count_1s(m_bitboard) * m_material_score);
}
