#ifndef PIECE_H
#define PIECE_H

#include <array>
#include <string>
#include "../../common/headers/common.h"
#include "../../graphics/headers/box.h"
#include "../../graphics/headers/pieces_drawings.hpp"
#include "../../common/headers/utils.h"
#include "../../game/headers/move.h"
#include "../../common/headers/direction.h"
#include "../../board/headers/BoardBitboard.h"

using namespace Direction;

class Piece {
 public:
    virtual ~Piece();
    bool is_black();
    Box* get_drawing(bool is_in_a_black);
    Piecetype get_type_and_color();
    bool is_black_piece(int pct);
    virtual bool is_legal_move(Move&, BoardBitboard&) = 0;

 protected:
    explicit Piece(const Piecetype&);
    U64 m_attacks[utils::constant::ksquares] = { BLANK };
    PieceDrawing* create_drawing(const Piecetype& m_type);

 private:
    StandardDrawingBuilder drawing_builder;
    Piecetype m_type;
    bool black = false;
    PieceDrawing* p_piece_drawing;
};

class IAttackMoves {
  public:
    virtual bool check_legal_attack_move(const Move&, BoardBitboard& board) = 0;
};

class INonAttackMoves {
  public:
    virtual bool check_legal_non_attack_move(Move&, BoardBitboard& board) = 0;
};

class ISpecialMoves {
  public:
    virtual bool is_special_move(Move&, BoardBitboard& board) = 0;
};

#endif /* PIECE_H */
