add_library(
  player_lib
  player.cpp
  players.cpp
  )

target_include_directories(player_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers"
)

message("Player library compiled")
