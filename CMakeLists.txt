# Version 3.8 is required for c++17
cmake_minimum_required(VERSION 3.8)
project(TOP-1 VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include(external/external.cmake)

add_subdirectory(src)
add_subdirectory(test)
