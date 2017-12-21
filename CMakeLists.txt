# Version 3.8 is required for c++17
cmake_minimum_required(VERSION 3.8)
project(OTTO VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_EXTENSIONS OFF)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(OTTO_DEBUG_UI "Enable the imgui based debug ui" ON)
option(OTTO_BUILD_DOCS "Build documentation" OFF)
option(OTTO_USE_LIBCXX "Link towards libc++ instead of libstdc++. This is the default on OSX" ${APPLE})
option(OTTO_ENABLE_TIMERS "Enable debugging timers" OFF)

if (OTTO_USE_LIBCXX)
  message("Using libc++ instead of libstdc++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

if (OTTO_ENABLE_TIMERS)
  add_definitions(-DOTTO_ENABLE_TIMERS=1)
else ()
  add_definitions(-DOTTO_ENABLE_TIMERS=0)
endif ()

if (OTTO_DEBUG_UI)
  add_definitions(-DOTTO_DEBUG_UI=1)
else()
  add_definitions(-DOTTO_DEBUG_UI=0)
endif()

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Wno-c++14-compat")
elseif(${CMAKE_CXX_COMPILER_ID} EQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Weverything -Wno-long-long -pedantic -Wno-c++14-compat")
endif()

include(external/external.cmake)

add_subdirectory(src)
add_subdirectory(test)
