#ifndef DIRECTION_H
#define DIRECTION_H

#include "defs.h"

namespace Direction {
/***********************************************************
 * Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
 * Copyright (C) 2008-2015 Marco Costalba, Joona Kiiski, Tord Romstad
 * Copyright (C) 2015-2019 Marco Costalba, Joona Kiiski, Gary Linscott, Tord Romstad
 * Stockfish, a UCI chess playing engine derived from Glaurung 2.1
 *************************************************************/
enum Direction : U64 {
  NORTH =  8,
  EAST  =  1,
  SOUTH = -NORTH,
  WEST  = -EAST,

  NORTH_NORTH = NORTH + NORTH,
  SOUTH_SOUTH = SOUTH + SOUTH,
  NORTH_EAST = NORTH + EAST,
  SOUTH_EAST = SOUTH + EAST,
  SOUTH_WEST = SOUTH + WEST,
  NORTH_WEST = NORTH + WEST
};

/***********************************************************
 * Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
 * Copyright (C) 2008-2015 Marco Costalba, Joona Kiiski, Tord Romstad
 * Copyright (C) 2015-2019 Marco Costalba, Joona Kiiski, Gary Linscott, Tord Romstad
 * Stockfish, a UCI chess playing engine derived from Glaurung 2.1
 *************************************************************/
constexpr U64 FileABB = 0x0101010101010101ULL;
constexpr U64 FileHBB = FileABB << 7;
/// shift() moves a bitboard one step along direction D
template<Direction D>
  constexpr U64 shift(U64 b) {
    return  D == NORTH  ?  b             << 8 : D == SOUTH      ?  b             >> 8
      : D == NORTH+NORTH?  b             <<16 : D == SOUTH+SOUTH?  b             >>16
      : D == EAST       ? (b & ~FileHBB) << 1 : D == WEST       ? (b & ~FileABB) >> 1
      : D == NORTH_EAST ? (b & ~FileHBB) << 9 : D == NORTH_WEST ? (b & ~FileABB) << 7
      : D == SOUTH_EAST ? (b & ~FileHBB) >> 7 : D == SOUTH_WEST ? (b & ~FileABB) >> 9
      : 0;
  }
}

#endif /* DIRECTION_H */
