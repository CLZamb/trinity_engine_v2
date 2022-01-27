add_library(
  logic_lib
  AiPlayer.cpp
  bitboard.cpp
  board.cpp
  magic_bitboard.cpp
  movement.cpp
  player.cpp
  )

target_include_directories(logic_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers"
)

message("logic library compiled")
