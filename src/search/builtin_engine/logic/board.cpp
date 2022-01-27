#include "board.h"

Board::Board() {}

Board::Board(Player* player1, Player* player2) {
  set_players(player1,player2);
  _init();
}

Board::~Board() {
  // Free each array and sub-array
  for (int i = 0; i < 64; ++i)
    delete p_squares[i];
}

void Board::_init() {
  m_bb._init();
  create_board_squares();
  parser_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
  movement_controller._init(turn->has_black_pieces());
}

void Board::set_players(Player* player1, Player* player2) {
  this->player1 = player1;
  this->player2 = player2;
  this->player1->set_opponent(this->player2);
  this->player2->set_opponent(this->player1);
  this->turn = player1;
}

void Board::undo_square_move(int piece, int piece_captured, SquareIndices from, SquareIndices to) {
  move_squares(m_bb.get_piece(piece), from, to);

  if (piece_captured)
    add_to_board(piece_captured, from);
}

void Board::move_piece_to_square(int piece, SquareIndices from, SquareIndices to) {
  move_squares(m_bb.get_piece(piece), from, to);
  move_piece_bits(piece, from, to);
}

void Board::move_squares(Piece* piece, SquareIndices from, SquareIndices to) {
  if (!piece || !get_square_at_pos(from) || !get_square_at_pos(to))
    return;

  get_square_at_pos(from)->clear_square();
  get_square_at_pos(to)->set_piece(piece);
}

Piece* Board::get_piece_at_square(int pos) {
  if (!get_square_at_pos(pos))
    return nullptr;

  return get_square_at_pos(pos)->get_piece();
}

PlayerMove Board::get_next_move() { return turn->get_next_move(); }
Player* Board::get_active_player() {  return turn; }
Player* Board::get_opponent() { return turn->get_opponent(); }

Board::Square* Board::get_square_at_pos(int pos) { return p_squares[pos]; }

void Board::create_board_squares() {
  char squareColor = 'w';

  int position = 0;
  // need to be ordered upside down
  for (int row = 7; row >= 0; --row) {
    for (int col = 0; col < 8; ++col) {
      position = row * 8 + col;
      if (squareColor == 'b') {
        squareColor = 'w';
        p_squares[position] = new Square(false);
      } else {
        squareColor = 'b';
        p_squares[position] = new Square(true);
      }
    }
    squareColor = squareColor == 'b' ? 'w' : 'b';
  }
}

void Board::parser_fen(string fen) {
  std::map <char, int> piece_map = {
    {'P', wP}, {'R', wR}, {'N', wN}, {'B', wB}, {'Q', wQ}, {'K', wK},
    {'p', bP}, {'r', bR}, {'n', bN}, {'b', bB}, {'q', bQ}, {'k', bK},
  };

  m_bb.reset_all_pieces_bitboard();

  SquareIndices square = A1;
  int rank = 7;
  int file = 0;
  int piece;

  for (char& c : fen) {
    piece = piece_map[c];
    if (piece) {
      square = static_cast<SquareIndices>(rank * 8 + file);
      m_bb.set_piece_at_pos(piece, square);
      add_to_board(piece, square);
      file++;

    } else if (is_number(c)) {
      file += (c - '0');

    } else if (c == '/') {
      rank--;
      file = 0;
    }

    if (rank < 0) break;
  }
}

void Board::add_to_board(int type, SquareIndices position) {
  get_square_at_pos(position)->set_piece(m_bb.get_piece(type));
}

bool Board::is_number(char c) {
  return c >= '0' && c <= '8';
}

void Board::undo_last_move() {
  movement_controller.undo_last_move();
}

void Board::make_move(PlayerMove p_mv) {
  Move move = p_mv.get_move();
  movement_controller.move_piece(move);

  string played_move = utils::get_piece_str_name(move.get_piece())
    + "-" +  p_mv.get_input();

  turn->save_played_moves(played_move);
}

bool Board::is_valid_move(Move mv) {
  return movement_controller.is_valid_move(mv);
}

bool Board::get_checkmate() {
  return movement_controller.get_checkmate();
}

Movement* Board::get_movement() {
  return &movement_controller;
}

void Board::generate_all_moves(bool side, MoveList* moveList) {
  return m_bb.generate_all_moves(side, moveList);
}

void Board::generate_all_cap_moves(bool side, MoveList* moveList) {
  return m_bb.generate_all_cap_moves(side, moveList);
}

void Board::move_piece_bits(int piece, SquareIndices from, SquareIndices to) {
  m_bb.make_move_bb(piece, from, to);
}

void Board::update_killers(Move mv) {
  m_bb.update_killers(mv);
}

void Board::update_search_history(int piece, int to, int depth) {
  m_bb.update_search_history(piece, to, depth);
}

void Board::capture_piece(Move mv, SquareIndices pos) {
  Piecetype captured_piece = mv.get_captured_piece();

  capture_piece_bit(captured_piece, pos);
  turn->save_captured_pieces(utils::get_piece_str_name(captured_piece));
}

void Board::change_turn() { turn = turn->get_opponent(); }
void Board::capture_piece_bit(int piece_captured, SquareIndices pos) {
  m_bb.capture_piece(piece_captured, pos);
}

void Board::undo_move(int piece, int piece_captured, SquareIndices from, SquareIndices to) {
  m_bb.undo_move(piece, piece_captured, from, to);
}

void Board::clear_killer_moves() { m_bb.clear_killer_moves(); }
void Board::clear_search_history() { m_bb.clear_search_history(); }
void Board::reset_ply() { m_bb.reset_ply(); }
int Board::get_ply() { return m_bb.get_ply(); }
void Board::increment_ply() { return m_bb.increment_ply(); }
void Board::deincrement_ply() { return m_bb.deincrement_ply(); }

U64 Board::get_piece_attacks(int type, int from) {
  return m_bb.get_piece_attacks(type, SquareIndices(from));
}

U64 Board::get_non_attack_moves(int type, int from) {
  return m_bb.get_non_attack_moves(type, SquareIndices(from));
}

U64 Board::get_own_pieces_occ(bool is_black) {
  if (is_black) return m_bb.get_all_b_bitboard();

  return  m_bb.get_all_w_bitboard();
}

U64 Board::get_all_pieces_bitboard() const {
  return m_bb.get_all_pieces_bitboard();
}

U64 Board::get_piece_bitboard(int piece) const {
  return m_bb.get_piece_bitboard(piece);
}

Piecetype Board::get_piece_at(int pos) {
  return m_bb.get_piece_at_pos(pos);
}

int Board::evaluate_board() { return m_bb.evaluate_board(); }

// Board::Square
Board::Square::Square(bool blackBox): m_is_black_square(blackBox) {}

Board::Square::~Square() {}

void Board::Square::set_piece(Piece* piece) {
  this->p_piece = piece;
}

void Board::Square::clear_square() {
  p_piece = nullptr;
}

bool Board::Square::is_black_square() { return m_is_black_square; }
Piece* Board::Square::get_piece() { return this->p_piece; }

