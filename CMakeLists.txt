# Version 3.8 is required for c++17
cmake_minimum_required(VERSION 3.8)
project(OTTO VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_EXTENSIONS OFF)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)

set(OTTO_DEBUG_UI ON)

include(external/external.cmake)

add_subdirectory(src)
add_subdirectory(test)
