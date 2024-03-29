#ifndef ISECTIONCOMPONENT_H
#define ISECTIONCOMPONENT_H

#include <vector>
#include <string>

using std::string;
using std::vector;

class Pane;
class ISectionComponent {
 public:
  explicit ISectionComponent(size_t size);

  vector<string>::iterator begin();
  vector<string>::iterator end();
  void set_parent_pane(Pane* parent);
  size_t size();

 protected:
  vector<string> m_section_drawing;

 private:
  const int m_size;
  Pane* parent_pane = nullptr;
};

#endif /* ISECTIONCOMPONENT_H */
