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

otto_option(RPI "Build for Raspberry Pi (native graphics)" OFF)

otto_option(ENABLE_TIMERS "Enable debugging timers" OFF)
otto_option(DEBUG_UI "Enable the imgui based debug ui" NOT OTTO_RPI)
otto_option(UI_EGL "Use EGL for the UI" OTTO_RPI)
otto_option(UI_GLFW "Use GLFW for the UI" NOT OTTO_RPI)
otto_option(AUDIO_ALSA "Use ALSA for audio" OTTO_RPI)
otto_option(AUDIO_JACK "Use JACK for audio" NOT OTTO_RPI)

otto_debug_definitions()

if (OTTO_USE_LIBCXX)
  message("Using libc++ instead of libstdc++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

add_subdirectory(external)


# Enable warnings for local code
if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -Wpedantic -Wno-c++14-compat -Wno-psabi -Wno-unknown-pragmas")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -Wpedantic \
-Wno-c++11-compat -Wno-c++98-compat -Wno-c++14-compat -Wc++17-compat \
-Wno-shadow-field-in-constructor \
-Wno-documentation-unknown-command \
-Wno-unknown-pragmas \
")
endif()

add_subdirectory(src)

if (OTTO_BUILD_TESTS)
  add_subdirectory(test)
endif()

