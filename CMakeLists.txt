cmake_minimum_required(VERSION 3.19)
project(SxTree CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -O0")

file(GLOB_RECURSE SX_SOURCES
        src/Lexer/*.cpp
        src/Exceptions/*.cpp
        src/AST/*.cpp
        src/IOTools/*.cpp)

add_executable(sxlgen src/Core/lexGen.cpp ${SX_SOURCES})
include_directories(include)
include_directories("${CMAKE_INSTALL_PREFIX}/include")

add_executable(SimpleExample examples/simple/lexer.cpp examples/simple/simpleExample.cpp ${SX_SOURCES})

link_libraries( Argumentum::argumentum)
