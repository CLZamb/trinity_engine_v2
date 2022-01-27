set(search search)

set(SOURCE_FILES
  main.cpp
  uci.cpp
  )

add_library(
  ${search}_lib
  ${SOURCE_FILES}
  )

add_executable(${search} ${SOURCE_FILES})

add_subdirectory(builtin_engine)

target_link_libraries(${search} PUBLIC general_lib)
target_link_libraries(${search} PUBLIC logic_lib)
target_link_libraries(${search} PUBLIC pieces_lib)
target_link_libraries(${search} PUBLIC search_search_lib)

target_include_directories(${search}_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers"
  )

target_include_directories(${search}  
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers"
  )

message("search library compiled")
