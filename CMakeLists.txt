cmake_minimum_required(VERSION 3.19)
project(SxTree CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -O0")

file(GLOB_RECURSE SX_SOURCES "src/*.cpp")
message("${SX_SOURCES}")
add_executable(tests tests.cpp ${SX_SOURCES})
include_directories(include)
