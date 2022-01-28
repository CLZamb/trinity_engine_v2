add_library(
  graphics_lib
  board_drawing.cpp
  game_drawings.cpp
  game_drawings_state.cpp
  Idisplay.cpp
  ISectionComponent.cpp
  pieces_drawings.cpp
  pane.cpp
  section.cpp
  square_drawing.cpp
  uicontroller.cpp
  view.cpp
  window.cpp
  )

target_include_directories(graphics_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers"
  )

message("graphics library compiled")
