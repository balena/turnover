cmake_minimum_required(VERSION 2.8)

project(turnover)

add_subdirectory(gtest)
config_compiler_and_linker()

macro(add_compile_flags)
  if(${ARGV0} MATCHES "BEFORE")
    set(CMAKE_CXX_FLAGS "${ARGV1} ${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "${ARGV1} ${CMAKE_CXX_FLAGS_DEBUG}")
    set(CMAKE_CXX_FLAGS_RELEASE "${ARGV1} ${CMAKE_CXX_FLAGS_RELEASE}")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${ARGV1} ${CMAKE_CXX_FLAGS_MINSIZEREL}")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${ARGV1} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
  elseif(${ARGV0} MATCHES "AFTER")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARGV1}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${ARGV1}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${ARGV1}")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${ARGV1}")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${ARGV1}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARGN}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${ARGN}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${ARGN}")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} ${ARGN}")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${ARGN}")
  endif()
endmacro()

if(UNIX)
  add_compile_flags(BEFORE "-std=c++0x -Wno-deprecated")
endif()

add_subdirectory(boost)

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

# Unit Tests
add_executable(turnover_tests
  crypto/crc32_unittest.cpp
  crypto/sha1_unittest.cpp
  crypto/md5_unittest.cpp
  crypto/hmac_unittest.cpp
)
add_dependencies(turnover_tests gtest gtest_main)
target_link_libraries(turnover_tests gtest gtest_main)
