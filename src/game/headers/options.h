#ifndef OPTIONS_H
#define OPTIONS_H

#include "../../player/headers/player.h"
#include <cstddef>
#include <iostream>
#include <unordered_map>

using std::unordered_map;

template <typename T> struct MenuItem {
  MenuItem(char c, string n, T o) : opt{o}, name{n}, option_key{c} {}
  MenuItem() = default;

  T opt{};
  string name{""};
  char option_key{'\0'};
};

template <typename T> class MenuList {
public:
  MenuList() {}
  MenuList(std::initializer_list<MenuItem<T>> lst) {
    for (auto &l : lst) {
      options.emplace(l.option_key, l);
    }
  }

  void add_options(T item) { options.emplace(options.size() - 1, item); }

  MenuItem<T> &find_at_index(const char& index) {
    return options.find(index)->second;
  }

  typename std::unordered_map<char, MenuItem<T>>::iterator begin() {
    return options.begin();
  }

  typename std::unordered_map<char, MenuItem<T>>::iterator end() {
    return options.end();
  }

  bool check_valid_option(const char& i) { return options.find(i) != options.end(); }

private:
  unordered_map<char, MenuItem<T>> options;
};

#endif /* OPTIONS_H */
