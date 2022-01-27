add_library(
  board_lib
  board.cpp
  board_with_info.cpp
  info.cpp
  square.cpp
)

target_include_directories(board_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers"
  )

message("board library compiled")
