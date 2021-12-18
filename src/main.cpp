#include "game/headers/game.h"
#include "game/headers/menu.h"

void play() {
  Menu<PlayerConfig> player_menu(
      {{1, "Player vs Player", {Player::Human, Player::Human}},
       {2, "Player vs Computer", {Player::Human, Player::Human}},
       {3, "Computer vs Computer", {Player::Human, Player::Human}}});

  player_menu.print_players_options();

  Game game(player_menu.select_option());
  game.start();
}

int main(/*int argc, char *argv[]*/) {
  string play_str = "play", quit = "quit";
  Menu<string> start_menu({{1, "Play Game", play_str},
                           {2, "Quit Game",  quit},
                           {3, "Config Game", quit}});

  start_menu.print_play_or_quit();

  if (start_menu.select_option() == play_str) {
    play();
  }

  return 0;
}
