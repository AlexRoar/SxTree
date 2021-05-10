cmake_minimum_required(VERSION 3.19)
project(SxTree CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -O0")

file(GLOB_RECURSE SX_SOURCES "src/*.cpp")

add_executable(sxlgen src/Core/lexGen.cpp ${SX_SOURCES})
include_directories(include)
include_directories("${CMAKE_INSTALL_PREFIX}/include")

message("${CMAKE_INSTALL_PREFIX}/include")

link_libraries( Argumentum::argumentum)
