#ifndef MOVE_UTILS_H
#define MOVE_UTILS_H

# pragma once

#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include"move.h"
#include"regex.h"

using std::string;

class String {
 public:
   static Move to_move(const string& str_move){
    std::vector<string> list_pos;
    Move result;

    list_pos = Regex::get_list_of_positions(str_move, format_single_position);

    if (list_pos.size() != 2) {
      return result;
    }

    int from = utils::square_str_to_int(list_pos[0]);
    int to = utils::square_str_to_int(list_pos[1]);

    result.set_move(from, to);
    return result;
  }

   static string to_str_move(string input) {
     std::vector<string> list_pos;
     list_pos = Regex::get_list_of_positions(input, format_single_position);
     return (list_pos.size() == 2) ? list_pos[0] + list_pos[1] : "";
   }

  static bool is_valid_move_format(const string& str_mv) {
    return Regex::match(str_mv, format_full_move);
  }

 private:
  inline static const std::regex format_full_move = std::regex("([a-hA-H][1-8]\\s*[a-hA-H][1-8])");
  inline static const std::regex format_single_position = std::regex("([a-hA-H]\\s*[1-8])");
};


#endif /* MOVE_UTILS_H */
