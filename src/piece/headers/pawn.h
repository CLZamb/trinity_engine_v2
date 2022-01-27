#ifndef PAWN_H
#define PAWN_H

#include "common/headers/bit_utilities.h"
#include "common/headers/direction.h"
#include "piece.h"

// template<Color C>
// constexpr U64 pawn_attacks_bb(U64 b) {
//   return C == WHITE ? ::shift<NORTH_WEST>(b) | ::shift<NORTH_EAST>(b)
//                     : ::shift<SOUTH_WEST>(b) | ::shift<SOUTH_EAST>(b);
// }
class PawnMove {
public:
  virtual ~PawnMove() {}
  virtual U64 pawn_attack(int) = 0;
  virtual U64 pawn_non_attack(int) = 0;
};

class BlackPawn : public PawnMove {
public:
  U64 pawn_attack(int sq) override;
  U64 pawn_non_attack(int sq) override;
};

class WhitePawn : public PawnMove {
public:
  U64 pawn_attack(int sq) override;
  U64 pawn_non_attack(int sq) override;
};

template <Color color>
class Pawn : public Piece,
             private IAttackMoves,
             private INonAttackMoves,
             private ISpecialMoves {
public:
  Pawn() : Piece(color == BLACK ? bP : wP) {
    if (color == BLACK) {
      pawn_moves = new BlackPawn();
    } else {
      pawn_moves = new WhitePawn();
    }
    init_masks();
  }

  virtual ~Pawn() { delete pawn_moves; }

  bool is_legal_move(Move &m, BoardBitboard &board) override {
    U64 to = ONE <<  m.get_to();

    const U64 opponent =
        board.get_all_side_pieces((color == BLACK) ? WHITE : BLACK);

    if (is_attack_move(to, opponent)) {
      return check_legal_attack_move(m, board);
    }

    return check_legal_non_attack_move(m, board);
  }

  bool is_attack_move(const U64 &to, const U64 &opponent) {
    return to & opponent;
  }

  bool is_special_move(Move &m, BoardBitboard &board) override {
    U64 to = ONE << m.get_to();

    U64 en_passant = board.get_en_passant(color == BLACK? WHITE : BLACK);

    if (en_passant & to) {
      U64 temp = en_passant & to;
      SquareIndices en_passant_to_remove = static_cast<SquareIndices>(bitUtility::pop_1st_bit(&temp));
      board.remove_en_passant(en_passant_to_remove, color);
      m.set_en_passant(true);

      return true;
    }

    return false;
  }

  bool check_legal_attack_move(const Move &m, BoardBitboard &board) override {
    U64 all_moves = BLANK;
    int from = m.get_from();
    U64 to = ONE << m.get_to();

    const U64 opponent =
        board.get_all_side_pieces((color == BLACK) ? WHITE : BLACK);

    all_moves |= m_attacks[from] & opponent; // enemy is that square occ
    return all_moves & to;
  }

  bool check_legal_non_attack_move(Move &m, BoardBitboard &board) override {
    U64 to = ONE << m.get_to();
    U64 from = ONE << m.get_from();
    const U64 free_squares = ~board.get_all_board_pieces();

    if (is_double_forward(from, to)) add_en_passant_move(m, board);

    if (is_special_move(m, board))
      return true;

    int sq_from = m.get_from();

    U64 all_moves = pawn_non_attack_mask(sq_from) & free_squares;
    if (all_moves & ROWMASK[7])
      m.set_promoted_piece(wQ);

    if (all_moves & ROWMASK[0])
      m.set_promoted_piece(bQ);

    return all_moves & to;
  }

private:
  bool is_double_forward(U64 from, U64 to) {
    if (color == WHITE)
      from = ::shift<NORTH_NORTH>(from);
    else 
      from = ::shift<SOUTH_SOUTH>(from);

    return to == from;
  }

  void add_en_passant_move(const Move& m, BoardBitboard &board) {
    int from = m.get_from();

    U64 to = ONE << m.get_to();
    if (color == BLACK) {
      if (to & ROWMASK[4]) {
        board.set_en_passant(static_cast<SquareIndices>(from - 8), color);
        board.set_en_passant(static_cast<SquareIndices>(from - 8), color);
      }
    } else {
      if (to & ROWMASK[3]) {
        board.set_en_passant(static_cast<SquareIndices>(from + 8), color);
        board.set_en_passant(static_cast<SquareIndices>(from + 8), color);
      }
    }
  }

  void init_masks() {
    for (int sq = 0; sq < utils::constant::ksquares; sq++)
      m_attacks[sq] = pawn_attack_mask(sq);
  }

  U64 pawn_attack_mask(int sq) {
    U64 pawn_mask = BLANK;
    pawn_mask = pawn_moves->pawn_attack(sq);
    return pawn_mask;
  }

  U64 pawn_non_attack_mask(int from_sq) {
    U64 result = ONE << from_sq;
    result = pawn_moves->pawn_non_attack(from_sq);
    return result;
  }

  U64 pawn_attacks_bb;
  PawnMove *pawn_moves;
};

#endif /* PAWN_H */
