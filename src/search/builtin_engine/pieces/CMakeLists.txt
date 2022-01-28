add_library(
  pieces_lib
  piece.cpp
  )

target_include_directories(pieces_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers"
)

message("Pieces library compiled")
