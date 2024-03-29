#include "search.h"
using std::cout;
using std::endl;

Search::Search(Board* board)
  : p_board(board), movement(board->get_movement())  {}

Search::~Search() {}
auto Search::get_time_now()  { return std::chrono::steady_clock::now(); }
auto Search::get_time_elapsed() {
  return std::chrono::duration_cast<std::chrono::milliseconds>
    (get_time_now() - m_start).count();
}

void Search::parser_fen(const string& fen) {
  p_board->parser_fen(fen);
}

bool Search::time_out() {
  return (get_time_elapsed() >= m_time_allocated) ? true : false;
}

void Search::clear_for_seach() {
  // movement->m_hash_table.clear();
  p_board->clear_search_history();
  p_board->clear_killer_moves();
  p_board->reset_ply();
}

Move Search::search_best_move() {
  cout << "started ";
  m_start = get_time_now();
  Move best_move;
  m_stop = false;
  clear_for_seach();

  cout << "computing ";
  int total_depth = 0;
  for (int currDepth = 1;  ; currDepth++) {
    total_depth = currDepth;
    best_move = root_negamax(currDepth);

    if (m_stop)
      break;

    if (get_time_elapsed() >= (m_time_allocated/2)) break;
  }

  cout << "sucess ";
  cout << "[Search info] ";
  cout << "Depth: " << total_depth  << " / ";
  cout << "Nodes: " << total_nodes << " / ";
  cout << "Elapsed time: " << get_time_elapsed() << " ms / ";
  cout << "best move: " 
    << utils::square_int_to_str(best_move.get_from())
    << utils::square_int_to_str(best_move.get_to());

  return best_move;
}

Move Search::root_negamax(int cur_depth) {
  int counter = 0;
  total_nodes = 0;

  int alpha = -utils::constant::kInfinite;
  int beta = utils::constant::kInfinite;
  int score = -utils::constant::kInfinite;

  MoveList m_legalMoves;
  generate_moves(&m_legalMoves);
  Move best_move = m_legalMoves.at(0);
  for (Move& mv : m_legalMoves) {
    pick_next_move(counter++, &m_legalMoves);
    movement->move_piece_bits(&mv);
    score = -negamax(cur_depth - 1, alpha, beta);
    movement->undo_last_bitboard_move(mv);

    if (m_stop || time_out()) {
      m_stop = true;
      break;
    }

    if (score > alpha) {
      best_move = mv;
      alpha = score;
    }
  }

  if (!m_stop) {
    movement->m_hash_table.set(
        movement->m_zkey, TTEntry(&best_move, alpha, cur_depth, TTEntry::EXACT));
  }

  return best_move;
}

/**
  negamax algorithm
    function negamax( depth, α, β, color)
    if depth = 0 or node is a terminal node then
    return color × the heuristic value of node

    childNodes := generateMoves(node)
    childNodes := orderMoves(childNodes)
    value := −∞
    foreach child in childNodes do
    value := max(value, −negamax(child, depth − 1, −β, −α, −color))
    α := max(α, value)
    if α ≥ β then
    break (* cut-off *)
  return value
*/
int Search::negamax(int depth, int alpha, int beta, bool do_null/*true*/) {
  if (m_stop || time_out()) {
    m_stop = true;
    return evaluate_board();
  }

  if (movement->checkmate)
    return evaluate_board();

  int orig_alpha = alpha;

  int hash_score = probe_hash_entry(depth, &alpha, &beta);
  if (hash_score)
    return hash_score;

  MoveList m_legalMoves;
  generate_moves(&m_legalMoves);

  if (m_legalMoves.empty()) {
    if (movement->checkmate)
      return evaluate_board();
    // draw
    return evaluate_board();
  }

  if (!depth)
    return quiescence_search(alpha, beta);

  int value = -utils::constant::kInfinite;

  if (do_null && p_board->get_ply() && depth >= 4) {
    make_null_move();
    value = -negamax(depth - 4, -beta, -beta + 1, false);
    take_null_move();
    if (m_stop) return evaluate_board();
    if (value >= beta) return beta;
  }

  int counter = 0;
  Move* best_move = &m_legalMoves.at(0);
  bool fullWindow = true;
  value = -utils::constant::kInfinite;
  for (Move& mv : m_legalMoves) {
    pick_next_move(counter++, &m_legalMoves);
    movement->move_piece_bits(&mv);
    if (fullWindow) {
      value = std::max(value, -negamax(depth - 1, -beta, -alpha));
    } else {
      value = std::max(value, -negamax(depth - 1, -alpha - 1, -alpha));
      if (value > alpha)
        value = std::max(value, -negamax(depth - 1, -beta, -alpha));
    }
    movement->undo_last_bitboard_move(mv);

    if (value > alpha) {
      fullWindow = false;
      alpha = value;
      best_move = &mv;
      if (!(mv.get_captured_piece()))
        p_board->update_search_history(mv.get_piece(), mv.get_to(), depth);
    }

    if (alpha >= beta) {
      best_move = &mv;
      if (!(mv.get_captured_piece()))
        p_board->update_killers(mv);
      break;
    }
  }

  TTEntry::Flag flag = get_flag(alpha, orig_alpha, beta);
  movement->m_hash_table.set(
      movement->m_zkey, TTEntry(best_move, alpha, depth, flag));

  return alpha;
}

/*
   int Quiesce( int alpha, int beta ) {
   int stand_pat = Evaluate();
   if( stand_pat >= beta )
   return beta;
   if( alpha < stand_pat )
   alpha = stand_pat;

   until( every_capture_has_been_examined )  {
   MakeCapture();
   score = -Quiesce( -beta, -alpha );
   TakeBackMove();

   if( score >= beta )
   return beta;
   if( score > alpha )
   alpha = score;
   }
   return alpha;
   }
 * */
int Search::quiescence_search(int alpha, int beta) {
  if (m_stop || time_out()) {
    m_stop = true;
    return evaluate_board();
  }

  if (p_board->get_ply() >= MAX_DEPTH)
    return evaluate_board();

  total_nodes++;
  int standPat = evaluate_board();

  if (standPat >= beta)
    return beta;

  if (alpha < standPat)
    alpha = standPat;

  MoveList m_legalMoves;
  generate_all_cap_moves(&m_legalMoves);

  if (m_legalMoves.empty())
    return evaluate_board();

  int counter = 0;
  for (Move& mv : m_legalMoves) {
    pick_next_move(counter++, &m_legalMoves);

    movement->move_piece_bits(&mv);
    int score = -quiescence_search(-beta, -alpha);
    movement->undo_last_bitboard_move(mv);

    if (score >= beta)
      return beta;

    if (score > alpha)
      alpha = score;
  }
  return alpha;
}

int Search::probe_hash_entry(
    const int &depth, int* alpha, int* beta) {
  const TTEntry* entry = movement->m_hash_table.get_entry(movement->m_zkey);
  if ((entry) && (entry->get_depth() >= depth)) {
    switch (entry->get_flag()) {
      case TTEntry::EXACT:
        return entry->get_score();
      case TTEntry::LOWER_BOUND:
        *alpha = std::max(*alpha, entry->get_score());
        break;
      case TTEntry::UPPER_BOUND:
        *beta = std::min(*beta, entry->get_score());
        break;
    }

    if (*alpha >= *beta)
      return entry->get_score();
  }

  return false;
}

TTEntry::Flag Search::get_flag(
    int alpha, int orig_alpha, int beta) {

  if (alpha <= orig_alpha) {
    return TTEntry::UPPER_BOUND;
  } else if (alpha >= beta) {
    return TTEntry::LOWER_BOUND;
  }

  return TTEntry::EXACT;
}

void Search::pick_next_move(int index, MoveList* moves) {
  int best_so_far = index;
  unsigned int best_score = 0;
  for (unsigned int i = index; i < moves->size(); ++i) {
    if (moves->at(i).get_score() > best_score) {
      best_score = moves->at(i).get_score();
      best_so_far = i;
    }
  }

  std::swap(moves->at(index), moves->at(best_so_far));
}

void Search::generate_moves(MoveList* legalMoves) {
  has_black_pieces = p_board->get_active_player()->has_black_pieces();
  p_board->generate_all_moves(has_black_pieces, legalMoves);
}

void Search::generate_all_cap_moves(MoveList* capMoves) {
  has_black_pieces = p_board->get_active_player()->has_black_pieces();
  p_board->generate_all_cap_moves(has_black_pieces, capMoves);
}

int Search::evaluate_board() {
  has_black_pieces = p_board->get_active_player()->has_black_pieces();
  if (has_black_pieces)
    return p_board->evaluate_board();

  return -p_board->evaluate_board();
}

void Search::make_null_move() {
  p_board->increment_ply();
  movement->change_turn();
}

void Search::take_null_move() {
  p_board->deincrement_ply();
  movement->change_turn();
}
