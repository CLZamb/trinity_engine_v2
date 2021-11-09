#include "headers/pieces.h"
#include "rook.cpp"
#include "bishop.cpp"
#include "queen.cpp"
#include "king.cpp"
#include "knight.cpp"

Pieces::Pieces() {
  create_all_pieces();
}

Pieces::~Pieces() {
  for (auto& i : m_pieces)
    delete i;
}

void Pieces::create_all_pieces() {
  // creating black pieces
  make_pawn(BLACK);
  make_rook(BLACK);
  make_bishop(BLACK);
  make_queen(BLACK);
  make_king(BLACK);
  make_knight(BLACK);

  // creating white pieces
  make_pawn(WHITE);
  make_rook(WHITE);
  make_bishop(WHITE);
  make_queen(WHITE);
  make_king(WHITE);
  make_knight(WHITE);
}

Piece* const Pieces::get_piece(int type) { return m_pieces[type]; }

void Pieces::make_pawn(const Color C) {
  if (C == BLACK)
    m_pieces[bP] = new Pawn<BLACK>;
  else
    m_pieces[wP] = new Pawn<WHITE>;
}

void Pieces::make_rook(const Color C) {
  if (C == BLACK)
    m_pieces[bR] = new Rook<BLACK>(m_magic_bitboard);
  else
    m_pieces[wR] = new Rook<WHITE>(m_magic_bitboard);;
}
//
void Pieces::make_bishop(const Color C) {
  if (C == BLACK)
    m_pieces[bB] = new Bishop<BLACK>(m_magic_bitboard);
  else
    m_pieces[wB] = new Bishop<WHITE>(m_magic_bitboard);
}
//
void Pieces::make_queen(const Color C) {
  if (C == BLACK)
    m_pieces[bQ] = new Queen<BLACK>(m_magic_bitboard);
  else
    m_pieces[wQ] = new Queen<WHITE>(m_magic_bitboard);
}

void Pieces::make_king(const Color C) {
  if (C == BLACK)
    m_pieces[bK] = new King<BLACK>;
  else
    m_pieces[wK] = new King<WHITE>;
}

void Pieces::make_knight(const Color C) {
  if (C == BLACK)
    m_pieces[bN] = new Knight<BLACK>;
  else
    m_pieces[wN] = new Knight<WHITE>;
}
