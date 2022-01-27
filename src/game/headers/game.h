#ifndef GAME_H
#define GAME_H

#include "../../graphics/headers/uicontroller.h"
#include "../../player/headers/player.h"
#include "../../player/headers/players.h"
#include "../headers/move_utils.h"
#include "game_turn_observable.h"
#include "ipc/headers/ipc_pipe.h"
#include "options.h"
#include "ipc/headers/cu_pipe.h"

class Game: public GameTurnObservable {
  public:
    Game(PlayerConfig);
    void start();

  private:
    bool is_valid_str_move_format(const string& move);
    bool is_legal_move(Move& move);
    void make_move(const Move& move);
    void play();
    void change_turn();
    void notify() override;
    void set_board_info(const string& input);
    void print_winner();
    bool game_players_exists();
    bool has_player_quit(const string& str);
    bool is_help_input(const string& str);
    string select_option(const string& play, const string& quit);
    string get_play_or_quit_selection();
    string get_current_player_input();
    BoardWithInfo m_board;
    Players players;
    size_t wrong_input_counter  = 0;
    static constexpr size_t max_wrong_input  = 3;
    GameTurn::players m_turn = GameTurn::player_1;
    IpcPipe m_ipc_search;
    std::shared_ptr<Player> game_turn;
    string initial_side = "";
    string help_info = 
        "Move ie - 'a2a3' - type 'quit', 'close' or 'exit' to end the game";
};


#endif /* GAME_H */
