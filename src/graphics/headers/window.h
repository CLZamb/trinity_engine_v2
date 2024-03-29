#ifndef WINDOW_H
#define WINDOW_H

#include <map>
#include "pane.h"
#include "section.h"
#include "../headers/Idisplay.h"
#include "../../common/headers/common.h"

using std::ostream;
using std::map;

class Window {
 public:
    enum Pane_pos {
      Left_pane = 0,
      Middle_pane = 1,
      Right_pane = 2,
      Max_panes_size = 3
    };

    Window();

    void add_displayable(Displayable* pane, Pane_pos pos);
    // int get_pane_size(int index);
    friend ostream& operator << (ostream &os,  Window &);

 private:
    void insert_formatted_output
      (map<int, Displayable*, std::less<int>> panes, ostream& os, int index);
    map<int, Displayable*, std::less<int>> panes;
};

#endif /* WINDOW_H */
