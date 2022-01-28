set(chess ${CMAKE_PROJECT_NAME})

set(SOURCE_FILES main.cpp)

add_executable(${chess} ${SOURCE_FILES})

add_subdirectory(board)
add_subdirectory(common)
add_subdirectory(graphics)
add_subdirectory(ipc)
add_subdirectory(game)
add_subdirectory(piece)
add_subdirectory(player)
add_subdirectory(search)

target_link_libraries(${chess} PUBLIC board_lib)
target_link_libraries(${chess} PUBLIC common_lib)
target_link_libraries(${chess} PUBLIC game_lib)
target_link_libraries(${chess} PUBLIC graphics_lib)
target_link_libraries(${chess} PUBLIC piece_lib)
target_link_libraries(${chess} PUBLIC player_lib)
target_link_libraries(${chess} PUBLIC ipc_lib)
target_link_libraries(${chess} PUBLIC search_lib)
