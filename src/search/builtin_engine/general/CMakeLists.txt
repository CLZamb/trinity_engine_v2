add_library(general_lib INTERFACE)

target_include_directories(general_lib
  INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/headers"
)

message("general library compiled")
