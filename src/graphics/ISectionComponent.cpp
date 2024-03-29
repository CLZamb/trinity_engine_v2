#include "ISectionComponent.h"

ISectionComponent::ISectionComponent(size_t size) : m_section_drawing(size), m_size(size) {}

void ISectionComponent::set_parent_pane(Pane* parent_pane) {
  if (this->parent_pane) return;
  if (!parent_pane) return;

  this->parent_pane = parent_pane;
}

size_t ISectionComponent::size() {
  return m_size;
}

vector<string>::iterator ISectionComponent::begin() {
  return m_section_drawing.begin();
}

vector<string>::iterator ISectionComponent::end() {
  return m_section_drawing.end();
}
