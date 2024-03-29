#ifndef BITBOARD_H
#define BITBOARD_H

#include <vector>
#include <string>
#include "move.h"
#include "../../pieces/headers/piece.h"
#include "../../logic/headers/magic_bitboard.h"
#include "../../general/headers/utils.h"

using std::string;

typedef std::vector<Move> MoveList;

class Bitboard {
 public:
    Bitboard();
    virtual ~Bitboard();
    void _init();

    U64 get_all_w_bitboard();
    U64 get_all_b_bitboard();
    U64 get_all_pieces_bitboard() const;
    U64 get_piece_bitboard(int piece) const;
    U64 get_Pieces_BB(int piece_type);
    U64 get_piece_attacks(int type, SquareIndices);
    U64 get_non_attack_moves(int type, SquareIndices);
    void generate_all_moves(bool side, MoveList*);
    void generate_all_cap_moves(bool side, MoveList*);
    void generate_all_black_moves(MoveList*);
    void clear_bit_at_player_pieces(bool is_black, SquareIndices pos);
    void move(int type, SquareIndices f, SquareIndices t);
    void capture_piece(int captured, SquareIndices pos);
    void put_piece_back(int captured, SquareIndices pos);
    void update_killers(Move mv);
    void update_search_history(int piece, int to, int depth);
    void make_move_bb(int piece, SquareIndices from, SquareIndices to);
    void undo_move(int piece, int piece_captured, SquareIndices from, SquareIndices to);
    void set_bit_at_player_pieces(bool is_black, SquareIndices pos);
    void reset_all_pieces_bitboard();
    void set_piece_at_pos(int piece, SquareIndices pos);
    void clear_search_history();
    void clear_killer_moves();
    void reset_ply();
    void increment_ply();
    void deincrement_ply();
    int evaluate_board();
    int get_movility_score(int piece);
    int get_ply();
    Piecetype get_piece_at_pos(int pos);
    Piece* get_piece(int type);

 private:
    int pop_1st_bit(U64* bb);
    int count_1s(U64 b);
    void _init_bitmasks();
    void _init_nonsliders_attacks();
    void _init_pieces_table_values();
    void _init_slider_masks_shifs_occupancies(int);
    void _init_tables(int);
    void _init_MvvLva();
    void gen_all_piece_moves(int type, MoveList* moveList, bool quiet = true);
    void gen_all_captured_moves(U64 dest, Move mv, MoveList* moveList);
    void gen_all_quiet_moves(U64 dest, Move mv, MoveList* moveList);
    // void gen_pawn_black_moves(int type, MoveList*, bool quite = true);
    // void get_pawn_white_moves(int type, MoveList*, bool quite = true);
    void gen_pawn_black_moves(MoveList* move_list, bool quite);
    void gen_pawn_black_quiet_moves(MoveList*);
    void gen_pawn_black_capture_moves(MoveList*);
    void generate_all_white_moves(MoveList*);
    void gen_pawn_white_quiet_moves(MoveList*);
    void gen_pawn_white_capture_moves(MoveList*);
    void add_quiet_move(Move quiet_move, MoveList* move_list);
    void add_captured_move(Move capture_move, MoveList* move_list);
    void add_en_pessant_move(Move ep_move, MoveList* move_list);
    U64 get_black_pawn_attacks(SquareIndices from);
    U64 get_white_pawn_attacks(SquareIndices from);
    U64 set_occupancy(int index, int bits, U64 m);
    U64 pawn_mask(int sq, int side);
    U64 knight_mask(int sq);
    U64 king_mask(int sq);
    Piece* m_pieces[13] {
      nullptr,  // EMPTY 0
      // black pieces
      new Piece(bP, PAWNSTART & ALLBLACKSTART),
      new Piece(bR, ROOKSTART & ALLBLACKSTART),
      new Piece(bN, KNIGHTSTART & ALLBLACKSTART),
      new Piece(bB, BISHOPSTART & ALLBLACKSTART),
      new Piece(bQ, QUEENSTART & ALLBLACKSTART),
      new Piece(bK, KINGSTART & ALLBLACKSTART),
      // white pieces
      new Piece(wP, PAWNSTART & ALLWHITESTART),
      new Piece(wR, ROOKSTART & ALLWHITESTART),
      new Piece(wN, KNIGHTSTART & ALLWHITESTART),
      new Piece(wB, BISHOPSTART & ALLWHITESTART),
      new Piece(wQ, QUEENSTART & ALLWHITESTART),
      new Piece(wK, KINGSTART & ALLWHITESTART),  // 12
    };

    int ply = 0;
    int pieces_score[13][utils::constant::squares] = {{0}};
    int MvvLvaScores[13][13];
    int search_history[13][utils::constant::squares] = {{0}};
    Move killers[2][utils::constant::kMaxDepth];
    MagicBitboard magic_bb;

    U64 m_all_w_pieces = ALLWHITESTART;
    U64 m_all_b_pieces = ALLBLACKSTART;
    U64 m_occupied = ALLWHITESTART|ALLBLACKSTART;

    U64 m_w_pawn_attacks[utils::constant::squares];
    U64 m_b_pawn_attacks[utils::constant::squares];
    U64 m_knight_attacks[utils::constant::squares];
    U64 m_king_attacks[utils::constant::squares];

    U64 Enpessant[2];
};

#endif /* BITBOARD_H */
