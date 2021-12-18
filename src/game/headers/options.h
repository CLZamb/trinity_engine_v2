#ifndef OPTIONS_H
#define OPTIONS_H

#include "../../player/headers/player.h"
#include <cstddef>
#include <iostream>
#include <unordered_map>

using std::unordered_map;

template <typename T> struct MenuItem {
  int number_option;
  string name;
  T opt;
};

template <typename T> class MenuList {
public:
  MenuList() {}
  MenuList(std::initializer_list<MenuItem<T>> lst) {
    for (auto &l : lst) {
      options.emplace(l.number_option, l);
    }
  }

  virtual ~MenuList() {}

  void add_options(T item) { options.emplace(options.size() - 1, item); }

  MenuItem<T> &find_at_index(size_t index) {
    return options.find(index)->second;
  }

  typename std::unordered_map<int, MenuItem<T>>::iterator begin() {
    return options.begin();
  }

  typename std::unordered_map<int, MenuItem<T>>::iterator end() {
    return options.end();
  }

  bool check_valid_option(int i) { return options.find(i) != options.end(); }

private:
  static const size_t start_index = 1;

  unordered_map<int, MenuItem<T>> options;
};

#endif /* OPTIONS_H */
