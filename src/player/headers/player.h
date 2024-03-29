// File: player.h
#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include <iostream>
#include <regex>
#include <string>
#include "../../common/headers/utils.h"

using std::string;

// template<Color color>
class Player {
 public:
   enum Type {
     Cpu = 0,
     Human = 1,
   };

   explicit Player(Color);
   void set_opponent(std::shared_ptr<Player> opponent);
   bool has_black_pieces();
   std::shared_ptr<Player> get_opponent();

   std::shared_ptr<Player> p_opponent = nullptr;
   Color color = Color::NONE;
   string color_str = "None";
   bool is_valid_input = false;
   bool m_black_pieces = false;
   int ply = 1;
};

// template<Color color>
struct PlayerConfig {
  Player::Type P1;
  Player::Type P2;
};

#endif /* PLAYER_H */
