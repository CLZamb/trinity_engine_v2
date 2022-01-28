add_library(
  common_lib
  common.cpp
  message.cpp
  )

target_include_directories(common_lib
          PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers"
          )
# add_executable(ipc ${SOURCE_FILES})
message("search library compiled")
