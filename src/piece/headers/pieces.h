#ifndef PIECES_H
#define PIECES_H 

#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "knight.h"

class Pieces {
 public:
    Pieces();
    virtual ~Pieces();
    Piece* const get_piece(int type);
    void make_pawn(const Color C);
    void make_rook(const Color C);
    void make_bishop(const Color C);
    void make_queen(const Color C);
    void make_king(const Color C);
    void make_knight(const Color C);

 private:
    MagicBitboard m_magic_bitboard;
    void create_all_pieces();
    std::array<Piece*, 13> m_pieces { nullptr };
    int m_size = 0;
    static const int m_max_size = 13;
};

#endif /* ifndef PIECES_H */