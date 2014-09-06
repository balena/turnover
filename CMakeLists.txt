cmake_minimum_required(VERSION 2.8)

add_subdirectory(boost)
add_subdirectory(gtest)

include_directories(boost gtest/include . src)
add_definitions(-DBOOST_ALL_NO_LIB)

# Turnover static library
#add_library(libturnover STATIC
#  src/server.hpp
#  src/server.cpp
#  src/request_handler.hpp
#  src/request_handler.cpp
#  src/message.hpp
#  src/attributes.hpp
#  src/connection_manager.hpp
#  src/connection_manager.cpp
#  src/connection.hpp
#  src/connection.cpp
#)

# Main executable
#add_executable(turnover
#  src/main.cpp
#)
#add_dependencies(turnover libturnover)
#target_link_libraries(turnover libturnover)

config_compiler_and_linker()

# Unit Tests
add_executable(turnover_tests
  crypto/sha1_unittest.cpp
  crypto/md5_unittest.cpp
)
add_dependencies(turnover_tests gtest gtest_main)
target_link_libraries(turnover_tests gtest gtest_main)
