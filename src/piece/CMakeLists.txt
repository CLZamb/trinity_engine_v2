add_library(
  piece_lib
  rook.cpp
  bishop.cpp
  king.cpp
  knight.cpp
  pawn.cpp
  queen.cpp
  piece.cpp
  pieces.cpp
  magic_bitboard.cpp
)

target_include_directories(piece_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers"
  )

message("piece library compiled")
