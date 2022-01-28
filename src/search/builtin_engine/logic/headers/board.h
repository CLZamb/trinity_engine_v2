// File: board.h
#ifndef BOARD_H
#define BOARD_H

#pragma once

#include <iostream>
#include <string>
#include <utility> // std::pair, std::make_pair
#include <vector>
#include "../../logic/headers/movement.h"

class Board {
 public:
  Board();
  Board(Player* player1, Player* player2);
  ~Board();

  void _init();
  void set_players(Player* player1, Player* player2);
  void undo_square_move(int piece, int piece_captured, SquareIndices from, SquareIndices to);
  void move_piece_to_square(int piece, SquareIndices from, SquareIndices to);
  void move_squares(Piece*, SquareIndices from, SquareIndices to);
  void capture_piece(Move mv, SquareIndices pos);
  void change_turn();
  Piece* get_piece_at_square(int);
  PlayerMove get_next_move();
  Player* get_active_player();
  Player* get_opponent();

  // adapter_pattern Movement
  void undo_last_move();
  void make_move(PlayerMove mv);
  bool is_valid_move(Move);
  bool get_checkmate();
  Movement* get_movement();

  // adapter_pattern Bitboard
  void generate_all_moves(bool side, MoveList* moveList);
  void generate_all_cap_moves(bool side, MoveList* mvl);
  void move_piece_bits(int type, SquareIndices from, SquareIndices to);
  void update_killers(Move mv);
  void update_search_history(int piece, int to, int depth);
  void capture_piece_bit(int piece_captured, SquareIndices pos);
  void undo_move(int piece, int piece_captured, SquareIndices from, SquareIndices to);
  void clear_killer_moves();
  void clear_search_history();
  void reset_ply();
  void increment_ply();
  void deincrement_ply();
  int get_ply();
  int evaluate_board();
  U64 get_piece_attacks(int type, int from);
  U64 get_non_attack_moves(int type, int from);
  U64 get_own_pieces_occ(bool is_black);
  U64 get_all_pieces_bitboard() const;
  U64 get_piece_bitboard(int piece) const;
  Piecetype get_piece_at(int pos);
  void parser_fen(string fen);

 private:
  class Square;
  void create_board_squares();
  void add_to_board(int piece, SquareIndices position);
  bool is_number(char c);
  char left_border(int row, int col);
  string right_border(vector<string> info, int col);
  string format_line(string tittle, string message);
  vector<string> get_board_info();

  Player* player1, *player2, *turn;
  Movement movement_controller{this};
  Bitboard m_bb;
  Square* p_squares[8 * 8 /*board size*/] = {nullptr};
  Square* get_square_at_pos(int pos);
};

class Board::Square {
 public:
    Square(bool);
    virtual ~Square();

    void set_piece(Piece* piece);
    void clear_square();
    char* at(int i);
    bool is_black_square();
    Piece* get_piece();

 private:
    Piece* p_piece = nullptr;
    bool m_is_black_square = false;
};

#endif /* BOARD_H */
