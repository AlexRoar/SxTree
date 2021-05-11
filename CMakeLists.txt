cmake_minimum_required(VERSION 3.19)

project(SxTree VERSION 0.2.0 DESCRIPTION "Generate AST syntax parser from grammar files" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

#[[Init]]
set(DEFAULT_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -O0")
include_directories(include)
include_directories("${CMAKE_INSTALL_PREFIX}/include")
add_subdirectory(googletest)

#[[Collect files]]
file(GLOB_RECURSE SX_SOURCES
        src/Lexer/*.cpp
        src/Exceptions/*.cpp
        src/AST/*.cpp
        src/IOTools/*.cpp)

file(GLOB_RECURSE SX_HEADERS
        include/*.h)

#[[Library]]
add_library(${PROJECT_NAME} SHARED "${SX_SOURCES}")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${SX_HEADERS}")
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)


#[[SxLexGenerator]]
add_executable(sxlgen src/Core/lexGen.cpp)

#[[Examples]]
add_executable(SimpleExample examples/simple/lexer.cpp examples/simple/simpleExample.cpp)

#[[Testing includes]]
enable_testing()
include(GoogleTest)

#[[Tests]]
add_executable(LexerGenTests tests/LexerGenerator/tests.cpp)
gtest_discover_tests(LexerGenTests)

#[[Links]]
target_link_libraries(SimpleExample ${PROJECT_NAME})
target_link_libraries(sxlgen ${PROJECT_NAME})
target_link_libraries(LexerGenTests gtest gtest_main ${PROJECT_NAME})


#[[Install]]
message("${CMAKE_INSTALL_INCLUDEDIR}")
install(TARGETS sxlgen
        RUNTIME DESTINATION "${PROJECT_NAME}/bin"
        PUBLIC_HEADER DESTINATION "${PROJECT_NAME}/lib")

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${PROJECT_NAME}/bin"
        LIBRARY DESTINATION "${PROJECT_NAME}/lib"
        ARCHIVE DESTINATION "${PROJECT_NAME}/bin"
        PUBLIC_HEADER DESTINATION "${PROJECT_NAME}/include")