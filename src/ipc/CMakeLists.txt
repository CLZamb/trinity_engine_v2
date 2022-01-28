add_library(
  ipc_lib
  ipc_pipe.cpp
  cu_pipe.cpp
  )

target_include_directories(ipc_lib
  PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers"
)
# add_executable(ipc ${SOURCE_FILES})

message("search library compiled")
