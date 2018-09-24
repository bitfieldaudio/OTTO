# Version 3.8 is required for c++17
cmake_minimum_required(VERSION 3.8)
project(OTTO VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_EXTENSIONS OFF)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/utils.cmake)

otto_option(BUILD_DOCS "Build documentation" OFF)
otto_option(BUILD_TESTS "Build tests" ON)
otto_option(USE_LIBCXX "Link towards libc++ instead of libstdc++. This is the default on OSX" ${APPLE})
otto_option(ENABLE_ASAN "Enable the adress sanitizer on development builds" OFF)

otto_option(ENABLE_TIMERS "Enable debugging timers" OFF)
otto_option(DEBUG_UI "Enable the imgui based debug ui" NOT OTTO_RPI)

if (OTTO_ENABLE_ASAN) 
  set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
  set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()

set(OTTO_BOARD "desktop" CACHE STRING "The board configuration to use")

file(GLOB OTTO_BOARDS RELATIVE ${OTTO_SOURCE_DIR}/boards/ ${OTTO_SOURCE_DIR}/boards/* )
list(REMOVE_ITEM OTTO_BOARDS parts)
set_property(CACHE OTTO_BOARD PROPERTY STRINGS ${OTTO_BOARDS})

if (OTTO_USE_LIBCXX)
  message("Using libc++ instead of libstdc++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(OTTO_EXTERNAL_DIR ${OTTO_SOURCE_DIR}/external/)

add_subdirectory(src)

otto_debug_definitions()

if (OTTO_BUILD_TESTS)
  add_subdirectory(test)
endif()

