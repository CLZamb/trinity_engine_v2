#include <gmock/gmock.h>
#include "../src/board/headers/board.h"
#include "../src/player/headers/players.h"
#include "../src/game/headers/move_utils.h"
#include "defs.h"
#include "queen.h"

using namespace testing;

class Aboard : public testing::Test {
  public:
    Board board;
};

TEST_F(Aboard, IsEmptyWhenCreated) {
  ASSERT_THAT(board.is_checkmate(), Eq(false));
}

TEST_F(Aboard, CheckLegalMoves) {
  Players players({Player::Human, Player::Human});
  Move m = String::to_move("a2a3");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));
  m = String::to_move("a2a4");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));
  m = String::to_move("h2f3");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(false));
}

TEST_F(Aboard, CheckLegaRooklMoves) {
  board.parser_fen("r6r/8/8/8/8/8/8/R6R");
  Players players({Player::Human, Player::Human});
  Move m = String::to_move("a1a3");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("a1a8");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("h8h1");
  ASSERT_THAT(board.is_legal_move(players.get_player_2(), m), Eq(true));
}

TEST_F(Aboard, check_get_fen) {
  string test = "r6r/8/8/8/8/8/8/R6R";
  board.parser_fen(test);

  ASSERT_THAT(board.get_fen() ,Eq(test));

  test = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

  board.parser_fen(test);
  ASSERT_THAT(board.get_fen() ,Eq(test));

  test = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R";
  board.parser_fen(test);

  Players players({Player::Human, Player::Human});
  Move m = String::to_move("a2a3");
  if (board.is_legal_move(players.get_player_1(), m))
    board.make_move(m);

  ASSERT_THAT(board.get_fen() ,Eq("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/P1N2Q1p/1PPBBPPP/R3K2R"));
}

TEST_F(Aboard, checklegalPawnMoves) {
  board.parser_fen("4k3/8/8/8/p1p2p2/1P4P1/8/4K3");
  Players players({Player::Human, Player::Human});
  Move m = String::to_move("b3c4");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("b3a4");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("g3f4");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("b3b4");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));
  board.make_move(m);

  m = String::to_move("b4b5");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));
  board.make_move(m);

  m = String::to_move("b5b6");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));
  board.make_move(m);

  m = String::to_move("b6b7");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));
  board.make_move(m);

  m = String::to_move("b7b8");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));
}

TEST_F(Aboard, checkLegalKnightMoves) {
  board.parser_fen("7k/8/1p1p4/p3p3/2N5/p3p3/1p1p4/7K");
  Players players({Player::Human, Player::Human});

  Move m = String::to_move("c4b2");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4a3");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4a5");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4b6");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4d6");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4e5");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4e3");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4d2");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));
}

TEST_F(Aboard, CheckLegalKingMoves) {
  board.parser_fen("7k/8/1p1p4/p3p3/2N5/p3p3/1p1p4/7K");
  Players players({Player::Human, Player::Human});

  Move m = String::to_move("c4b2");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4a3");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4a5");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4b6");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4d6");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4e5");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4e3");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("c4d2");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));
}

TEST_F(Aboard, checkeLegalQueenMoves) {
  board.parser_fen("K5pQ/8/8/4n3/3N4/8/8/qP5k");
  Players players({Player::Human, Player::Human});

  Move m = String::to_move("h8h1");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("h8g8");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));

  m = String::to_move("h8e5");
  ASSERT_THAT(board.is_legal_move(players.get_player_1(), m), Eq(true));


  m = String::to_move("a1a8");
  ASSERT_THAT(board.is_legal_move(players.get_player_2(), m), Eq(true));

  m = String::to_move("a1b1");
  ASSERT_THAT(board.is_legal_move(players.get_player_2(), m), Eq(true));

  m = String::to_move("a1d4");
  ASSERT_THAT(board.is_legal_move(players.get_player_2(), m), Eq(true));
}

TEST_F(Aboard, CheckMoveEnPassant) {
  Move m;
  m.set_en_passant(true);
  ASSERT_THAT(m.is_en_passant(), Eq(true));
  m.set_en_passant(false);
  ASSERT_THAT(m.is_en_passant(), Eq(false));
}

TEST_F(Aboard, CheckMoveIsCastel) {
  Move m;
  m.set_is_castle(true);
  ASSERT_THAT(m.is_castle(), Eq(true));
  m.set_is_castle(false);
  ASSERT_THAT(m.is_castle(), Eq(false));
}

TEST_F(Aboard, CheckMovePromotion) {
  Move m;
  m.set_promoted_piece(bQ);
  ASSERT_THAT(m.get_promoted_piece(), Eq(bQ));
}

// TEST_F(Aboard, CheckMovePromotion) {
//   Move m;
//   m.set_promoted_piece(bQ);
//   ASSERT_THAT(m.get_promoted_piece(), Eq(bQ));
//
// }


