#include "game/headers/game.h"
#include "game/headers/menu.h"

inline void play() {
  Menu<PlayerConfig> player_menu(
      {{'1', "Player vs Player", {Player::Human, Player::Human}},
       {'2', "Player vs Computer", {Player::Human, Player::Human}},
       {'3', "Computer vs Computer", {Player::Human, Player::Human}}});

  player_menu.print_menu();
  Game game(player_menu.select_option());
  game.start();
}

int main(/*int argc, char *argv[]*/) {
  // string player_input;
  // IpcPipe m_ipc_search;
  // m_ipc_search._init();

  // player_input = m_ipc_search.get_result();
  // cout << player_input << endl;
  // string test = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  // m_ipc_search.send_request("position " + test);
  // m_ipc_search.send_request("go");
  // player_input = m_ipc_search.get_result();
  // cout << player_input << endl;
  // //
  // test = "r6r/8/8/8/8/8/8/R6R";
  // m_ipc_search.send_request("position " + test);
  // m_ipc_search.send_request("go");
  // player_input = m_ipc_search.get_result();
  // cout << player_input << endl;
  // //
  // test = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R";
  // m_ipc_search.send_request("position " + test);
  // m_ipc_search.send_request("go");
  // player_input = m_ipc_search.get_result();
  // cout << player_input << endl;
  //
  // player_input = m_ipc_search.get_result();
  // cout << player_input << endl;
  //
  string play_str = "play", quit = "quit", config = "config";
  Menu<string> start_menu({{'1', "Play Game", play_str},
                           {'2', "Quit Game", quit},
                           {'3', "Config Game", config}});

  start_menu.print_menu();
  if (start_menu.select_option() == play_str) {
    play();
  }
  return 0;
}
