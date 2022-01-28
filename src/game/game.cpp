#include "game.h"

Game::Game(PlayerConfig pc)
    : players(pc), m_turn(GameTurn::player_1),
      initial_side(GameTurn::player_1 == m_turn ? "white" : "black") {
  attach(&m_board);
  game_turn = (GameTurn::player_1 == m_turn) ? players.get_player_1()
                                             : players.get_player_2();
  m_ipc_search._init();
}

void Game::start() {
  set_board_info("Is player " + initial_side + " turn");
  this->play();
}

void Game::play() {
  BoardView m_board_view(&m_board);
  string player_input = "";
  Move player_move;

  while (!m_board.is_checkmate()) {
    m_board_view.print();
    player_input = get_current_player_input();

    if (has_player_quit(player_input))
      return;

    // if (has_player_undo_move(player_input))
    //   break;

    if (is_help_input(player_input))
      continue;

    if (player_input == "cpu") {
      m_ipc_search.request("position " + m_board.get_fen());
      player_input = m_ipc_search.request("go");
      player_input = String::to_str_move(player_input);
    }

    if (!is_valid_str_move_format(player_input))
      continue;

    player_move = String::to_move(player_input);
    if (is_legal_move(player_move)) {
      make_move(player_move);
      change_turn();
    }
  }
   
  print_winner();
  std::cin.get();
};

void Game::print_winner() {
  change_turn();

  bool has_player_1_won;
  if (m_turn == GameTurn::player_1)
    has_player_1_won = true;
  else // current_player == player_2
    has_player_1_won = false;

  WinnerView win_view(has_player_1_won);
  win_view.print();
};

void Game::make_move(const Move &m) {
  m_board.make_move(m);
}

bool Game::is_valid_str_move_format(const string &input) {
  if (String::is_valid_move_format(input))
    return true;

  set_board_info("Move { " + input +
                 " } - is an not in a recognizable format, please try again ");

  wrong_input_counter++;
  if (wrong_input_counter == max_wrong_input) {
    set_board_info(help_info);
    wrong_input_counter = 0;
  }

  return false;
}

bool Game::is_legal_move(Move & m) {
  if (!m_board.is_legal_move(game_turn, m)) {
    // set_board_info("Move { " + str_player_move + " } is an ilegal move");
    return false;
  }

  return true;
}

bool Game::has_player_quit(const string &str) {
  return str == "quit" || str == "close" || str == "exit";
}

bool Game::is_help_input(const string &input) {
  if (input == "help") {
    set_board_info(help_info);
    return true;
  }

  return false;
}

void Game::change_turn() {
  game_turn = game_turn->get_opponent();

  if (m_turn == GameTurn::player_2)
    m_turn = GameTurn::player_1;
  else // current_player == player_2
    m_turn = GameTurn::player_2;

  notify();
}

void Game::notify() {
  for (auto observer : *_observers) {
    observer->update_turn(m_turn);
  }
}

string Game::get_current_player_input() {
  string input;
  std::cout << std::endl << " >> ";
  std::getline(std::cin, input);
  std::cout << std::endl;
  return input;
}

void Game::set_board_info(const string &info) {
  m_board.update_game_info(info);
}
