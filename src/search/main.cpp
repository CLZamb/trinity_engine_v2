#include <iostream>
#include "builtin_engine/logic/headers/board.h"
#include "search/builtin_engine/logic/headers/AiPlayer.h"
#include "uci.h"
#include "player/headers/player.h"

// using std::cout;
// using std::cin;
// using std::endl;
// using std::cerr;
/*
argc	-	Non-negative value representing the number of arguments
        passed to the program from the environment in which thez
        program is run.
argv	-	Pointer to the first element of an array of argc + 1 pointers,
        of which the last one is null and the previous ones, if any,
        point to null-terminated multibyte strings that represent
        the arguments passed to the program from the execution environment.
        If argv[0] is not a null pointer (or, equivalently, if argc > 0),
        it points to a string that represents the name used to invoke the program,
        or to an empty string.

by default argv[0] == name of the program
eg. argv[0] = ./search
    argv size is 1
*/


/*
 * When the user passes a command the program run that command
 * and quits the program
 */

int main(int argc, char *argv[]) {
  if (argv[1] == nullptr) {
    argv[1] = const_cast<char*>("");
    argc++;
  }

  Board m_board;
  Search engine(&m_board);
  AiPlayer player1(WHITE, engine);
  Player player2(BLACK);

  m_board.set_players(&player1, &player2);
  m_board._init();
  m_board.change_turn();

  UCI::Handler uci(&engine);
  uci.loop(argv[1]);
  return 0;
}
