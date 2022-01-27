#include "board.h"
#include "common/headers/defs.h"

Board::Board(string fen /*"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"*/) {
  create_board_squares();
  parser_fen(fen);
}

bool Board::is_checkmate() { return checkmate; }

bool Board::is_legal_move(std::shared_ptr<Player> turn, Move &m) {
  if (!exist_piece_at_square(m.get_from()))
    return false;

  if (!check_piece_belongs_to_current_player(turn, m.get_from()))
    return false;

  Piece *piece = get_piece_at_square(m.get_from());

  return piece->is_legal_move(m, board_state);
}

bool Board::exist_piece_at_square(const int &pos) {
  return get_piece_at_square(pos);
}

bool Board::check_piece_belongs_to_current_player(std::shared_ptr<Player> turn,
                                                  const int &pos) {
  Piece *piece = get_piece_at_square(pos);
  if (!piece)
    return false;
  return piece->is_black() == turn->has_black_pieces();
}

void Board::make_move(const Move &mv) {
  SquareIndices from = mv.get_from();
  SquareIndices to = mv.get_to();
  Piece *piece = get_piece_at_square(from);
  Piece *captured = get_piece_at_square(to);

  if (captured && 
      ((captured->get_type_and_color() == bK) ||
      (captured->get_type_and_color() == wK)))
    checkmate = true;

  if (mv.is_en_passant()) {
    if (piece->is_black())
      get_square_at_pos(to + 8).clear_square();
    else 
      get_square_at_pos(to - 8).clear_square();
  }

  if (mv.is_castle()) {
    if (abs(from - to) == 2) {
      Piece *rook;
      if (from > to) {  // queen castle
        rook = get_square_at_pos(to - 2).get_piece();
        if (rook->get_type_and_color() == bR || rook->get_type_and_color() == wR) {
          get_square_at_pos(to + 1).set_piece(rook);
          get_square_at_pos(to - 2).clear_square();
        }
      } else {  // king castle
        rook = get_square_at_pos(to + 1).get_piece();
        if (rook->get_type_and_color() == bR || rook->get_type_and_color() == wR) {
          get_square_at_pos(to - 1).set_piece(rook);
          get_square_at_pos(to + 1).clear_square();
        }
      }
    }
  }

  if (mv.get_promoted_piece() != EMPTY) {
    piece = m_pieces.get_piece(mv.get_promoted_piece());
  }

  board_state.move(piece->is_black(), from, to);
  move_piece_to_square(piece, from, to);
}

// void Board::place_piece();
// void Board::remove_piece();

bool Board::is_captured_move(const Move &m) {
  return utils::check::is_valid_piece(m.get_captured_piece());
}

void Board::capture_piece(const Move &m) {}

void Board::move_piece_to_square(Piece *pc, SquareIndices from,
                                 SquareIndices to) {
  if (!pc)
    return;

  get_square_at_pos(from).clear_square();
  get_square_at_pos(to).set_piece(pc);
}

Piece *Board::get_piece_at_square(int pos) {
  return get_square_at_pos(pos).get_piece();
}

void Board::create_board_squares() {
  char squareColor = 'w';
  bool is_black_squared = true;

  int position = 0;
  const int col_size = 7;
  const int row_size = 8;
  /*
   * Rows needs to be ordered upside down
   * because the program prints from top to bottom
   * so that 8 should be printed frist
   */

  for (int row = col_size; row >= 0; --row) {
    for (int col = 0; col < row_size; ++col) {
      /*
       * there are 8*8 (from 0 to 63) squares
       * to get the position
       * we need to multyply rwo by 8 and add the col
       * i.e the bottom right position would be
       * 8 * 0 + 7 = 7
       * */
      position = row * 8 + col;
      if (squareColor == 'b') {
        squareColor = 'w';
        m_squares[position].set_color(!is_black_squared);
      } else {
        squareColor = 'b';
        m_squares[position].set_color(is_black_squared);
      }
    }
    squareColor = squareColor == 'b' ? 'w' : 'b';
  }
}

void Board::parser_fen(string fen) {
  clear_board();
  SquareIndices square = A1;
  int rank = 7;
  int file = 0;
  int piece;

  for (const char &c : fen) {
    piece = utils::get_square_index_from_char_key(c);
    if (piece) {
      square = static_cast<SquareIndices>(rank * 8 + file);
      add_to_board(piece, square);

      file++;

    } else if (is_number(c)) {
      file += (c - '0');

    } else if (c == '/') {
      rank--;
      file = 0;
    }

    if (rank < 0)
      break;

    // if (c == 'w') turn(white);
    // if (c == 'b') turn(black);
  }
}

string Board::get_fen() {
  Square square;
  Piece *pc;
  string fen = "";
  int space = 0;
  auto print_empty = [&](int &space) {
    if (space) {
      fen += std::to_string(space);
    }
    space = 0;
  };

  for (int rank = 7; rank >= 0; rank--) {
    for (int file = 0; file <= 7; file++) {
      square = get_square_at_pos(rank * 8 + file);
      pc = square.get_piece();
      if (pc) {
        print_empty(space);
        fen += utils::piecetype_to_char(pc->get_type_and_color());
      } else {
        space++;
      }
    }
    if (rank > 0) {
      print_empty(space);
      fen += "/";
    }
  }
  return fen;
}

void Board::clear_board() {
  int pos = 0;
  bool is_black = false;
  for (auto &square : m_squares) {
    square.clear_square();
    board_state.clear_bit_at_player_pieces(is_black,
                                           static_cast<SquareIndices>(pos));
    board_state.clear_bit_at_player_pieces(!is_black,
                                           static_cast<SquareIndices>(pos));
    pos++;
  }
}

void Board::add_to_board(int type, SquareIndices position) {
  get_square_at_pos(position).set_piece(m_pieces.get_piece(type));
  board_state.set_bit_at_player_pieces(utils::check::is_black_piece(type),
                                       position);
}

bool Board::is_number(char c) { return c >= '0' && c <= '8'; }

Square &Board::get_square_at_pos(int pos) { return m_squares[pos]; }

Displayable *Board::get_drawing() { return &m_bdrawing; }
