#ifndef UCI_H
#define UCI_H
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "search/builtin_engine/search/headers/search.h"
#include "search/builtin_engine/logic/headers/AiPlayer.h"

namespace UCI {
class Handler {
 public:
  explicit Handler(Search* search);
  virtual ~Handler();
  void loop(const string& args);
  void uci_command();
  void is_ready_command();
  void set_option_command(std::istringstream &inStream);
  void uci_new_game_command();
  void position_command(std::istringstream &inStream);
  void go_command(std::istringstream &inStream);
  void stop_command();
  void ponder_hit_command();
  void register_command();
  void debug_command();
  void noop();
 private:
  Search* p_search;
};
}  // namespace UCI

#endif /* UCI_H */
