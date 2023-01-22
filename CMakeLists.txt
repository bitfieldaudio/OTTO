cmake_minimum_required(VERSION 3.14)
project(OTTO VERSION 0.0.1 LANGUAGES CXX C)


set(CMAKE_CXX_EXTENSIONS OFF)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0" CACHE STRING "" FORCE)

include(cmake/utils.cmake)

otto_option(BUILD_DOCS "Build documentation" OFF)
otto_option(BUILD_TESTS "Build tests" ON)
otto_option(USE_LIBCXX "Link towards libc++ instead of libstdc++. This is the default on OSX" ${APPLE})
otto_option(ENABLE_ASAN "Enable the adress sanitizer on development builds" OFF)
otto_option(ENABLE_UBSAN "Enable the undefined behaviour sanitizer on development builds" OFF)
otto_option(ENABLE_TSAN "Enable the thread sanitizer on development builds" OFF)
otto_option(ENABLE_LTO "Enable link time optimization on release builds. Only works on clang" OFF)
otto_option(TWEAKS_ENABLED "Enable runtime-tweakable parameters useful for development" OFF)

include(cmake/CPM.cmake)
set(CPM_USE_LOCAL_PACKAGES OFF)
set(CPM_LOCAL_PACKAGES_ONLY OFF)

if (OTTO_ENABLE_ASAN) 
  set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fno-sanitize=vptr")
  set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -fno-sanitize=vptr")
endif()

if (OTTO_ENABLE_UBSAN)
  set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined")
  set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=undefined")
endif()

if (OTTO_ENABLE_TSAN)
  set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=thread")
  set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=thread")
endif()

if (DEFINED CMAKE_CXX_FLAGS_DEBUG_INIT AND  
    "${CMAKE_CXX_FLAGS_DEBUG_INIT}" STREQUAL "${CMAKE_CXX_FLAGS_DEBUG}")
    # Overwrite the init values choosen by CMake
    if (CMAKE_COMPILER_IS_GNUCXX)
    endif()
endif()

option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." FALSE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-backtrace-limit=0")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  # set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts-diagnostics-depth=1000")
endif()

set(OTTO_BOARD "desktop" CACHE STRING "The board configuration to use")

file(GLOB OTTO_BOARDS RELATIVE ${OTTO_SOURCE_DIR}/boards/ ${OTTO_SOURCE_DIR}/boards/* )
list(REMOVE_ITEM OTTO_BOARDS parts)
set_property(CACHE OTTO_BOARD PROPERTY STRINGS ${OTTO_BOARDS})

if (OTTO_USE_LIBCXX)
  message(FATAL_ERROR "libc++ support is currently disabled, until it supports more of c++17/20. "
    "Use a recent version of libstdc++ instead, and set OTTO_USE_LIBCXX to false in cmake. ")
  message("Using libc++ instead of libstdc++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10.2)
        message(FATAL_ERROR "GCC version must be at least 10.2!")
    endif()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10.0)
        message(FATAL_ERROR "Clang version must be at least 10.0!")
    endif()
else()
    message(WARNING "You are using an unsupported compiler! Compilation has only been tested with Clang and GCC.")
endif()

set(OTTO_EXTERNAL_DIR ${OTTO_SOURCE_DIR}/external/)

if (NOT OTTO_BUILD_TESTS)
  add_compile_definitions(DOCTEST_CONFIG_DISABLE=1)
endif()

# Enable warnings for local code
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(OTTO_CXX_FLAGS "-Wall -Wno-long-long \
-Wno-c++14-compat -Wno-psabi \
-Wno-unknown-pragmas \
-Wno-vla \
-Wno-sign-compare \
-Wno-error=pedantic \
-Werror=unused-result \
")
# Don't remove unused-result, use [[maybe_unused]] to circumvent necessary
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(OTTO_CXX_FLAGS "-Wall -Wno-long-long \
-Wno-c++11-compat -Wno-c++98-compat -Wno-c++14-compat -Wno-c++17-compat -Wc++20-compat \
-Wno-shadow-field-in-constructor \
-Wno-documentation-unknown-command \
-Wno-unknown-pragmas \
-Wno-missing-braces \
-Wno-vla-extension \
-Wno-c99-extensions \
-Wno-gnu-zero-variadic-macro-arguments \
-Wno-gnu-anonymous-struct \
-Wno-nested-anon-types \
-Werror=unused-result \
")
# Don't remove unused-result, use [[maybe_unused]] to circumvent when necessary
endif()

add_subdirectory(src)

otto_debug_definitions()

if (OTTO_BUILD_TESTS)
  add_subdirectory(test)
endif()

if (OTTO_ENABLE_LTO) 
  include(CheckIPOSupported)
  check_ipo_supported(RESULT supported OUTPUT error)

  if( supported )
    message(STATUS "IPO / LTO enabled")
    set_property(TARGET otto_exec PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    set_property(TARGET otto_test PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(STATUS "IPO / LTO not supported: <${error}>")
  endif()
endif()
