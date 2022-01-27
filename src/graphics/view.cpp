#include "view.h"

// View::View()  {}
View::View(string name) {
  this->_name = name;
}

void View::print() {
  cout << window_view << endl;
}

string View::Get_name() {
  return _name;
}

string View::_name{ "" }; // initializer

    // static string name;
