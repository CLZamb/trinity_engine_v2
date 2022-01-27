add_library(
  game_lib
  game.cpp
  game_turn_observable.cpp
  move_utils.cpp
  menu.cpp
  options.cpp
)

target_include_directories(game_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers"
  )

message("game library compiled")
