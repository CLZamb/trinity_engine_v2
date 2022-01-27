add_library(
  search_search_lib
  search.cpp
  transposition_table.cpp
  transposition_table_entry.cpp
  Zobristkey.cpp
  )

target_include_directories(search_search_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers"
)

message("search search library compiled")
