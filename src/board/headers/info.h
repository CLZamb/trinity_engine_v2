#ifndef INFO_H
#define INFO_H

// #include <string>
// #include "utils.h"
#include <array>
#include <assert.h>     /* assert */
#include <memory>
#include <map>
#include <string>
#include <vector>
#include "../../graphics//headers/pieces_drawings.hpp"
#include "savable.h"
#include "../../graphics//headers/game_drawings.hpp"
#include "../../graphics//headers/Idisplay.h"
#include "../../graphics//headers/section.h"
#include "../../game/headers/game_turn_observer.h"

using std::vector;
using std::string;
using std::make_unique;
using std::shared_ptr;

using players = GameTurn::players;

class Info : public Displayable, public Savable {
 public:
    Info();
    virtual ~Info();
    void draw();
    void save_move(const string& moves);
    void save_capture(const string& moves);
    void save_game_info(const string& info);
    void update_turn(GameTurn::players turn);

 private:
    const unsigned int kRowMaxLen = Banner::width - 4/*┃  ┃*/;
    void start_or_quit_selection();
    void clear_block();
    void set_content_to_block_recursively(
        shared_ptr<Section>&, string msg, int cur_row);
    void format_block(shared_ptr<Section>&, string msg);
    void clear();
    bool has_block_space_for_content(
        const shared_ptr<Section>& block, const string& message);
    string format_line(string);
    string get_turn_info(GameTurn::players turn);

    std::array<const vector<string>*, Info::players_size>
      p_banners {
        &Banner::player1,
        &Banner::player2
      };

    GameTurn::players m_turn = GameTurn::players::player_1;
    string board_score;

    shared_ptr<Section>  p_top_section = make_unique<Section>("top", 1);
    shared_ptr<Section> p_player_banner = make_unique<Section>("Player banner", p_banners[m_turn]->size());
    shared_ptr<Section> p_board_score = make_unique<Section>("[Board Score]", 4);
    shared_ptr<Section> p_player_2_captures = make_unique<Section>("[Black captures]", 4);
    shared_ptr<Section> p_player_1_captures = make_unique<Section>("[White Captures]", 4);
    shared_ptr<Section> p_player_2_moves = make_unique<Section>("[Black moves]", 9);
    shared_ptr<Section> p_player_1_moves = make_unique<Section>("[White Moves]", 9);
    shared_ptr<Section> p_game_info = make_unique<Section>("[Game info]", 5);
    shared_ptr<Section> p_bottom_section = make_unique<Section>("bottom", 1);
};

#endif /* INFO_H */
