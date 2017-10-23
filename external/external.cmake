set(CMAKE_CXX_STANDARD 17)

# Generate gl3w files
include("${CMAKE_CURRENT_SOURCE_DIR}/external/gl3w_gen.cmake")
gl3w_gen("${CMAKE_CURRENT_SOURCE_DIR}/external/")

# General purpose externals (header only only)
file(GLOB_RECURSE external_src
  "${CMAKE_CURRENT_SOURCE_DIR}/external/src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/src/*.cpp"
  )
add_library(external ${external_src})
target_include_directories(external PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/include)

# Nanovg
execute_process(COMMAND git submodule update --init -- external/nanovg
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE nanovg_src "${CMAKE_CURRENT_SOURCE_DIR}/external/nanovg/src/*.c")
add_library(nanovg ${nanovg_src})
target_include_directories(nanovg INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/external/nanovg/src)

# Use GL3 on OSX, and GLES3 on linux
if (APPLE)
  find_package(OpenGL)
  target_include_directories(nanovg INTERFACE ${OPENGL_INCLUDE_DIR})
  target_link_libraries(nanovg INTERFACE ${OPENGL_LIBRARIES})
else ()
endif()

# NanoCanvas
execute_process(COMMAND git submodule update --init -- external/NanoCanvas
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE nanocanvas_src "${CMAKE_CURRENT_SOURCE_DIR}/external/NanoCanvas/src/*.cpp")
add_library(nanocanvas ${nanocanvas_src})
target_link_libraries(nanocanvas nanovg)
target_include_directories(nanocanvas INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/external/NanoCanvas/src)

# Imgui
execute_process(COMMAND git submodule update --init -- external/imgui
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB imgui_src
  "${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/imgui/imgui_draw.cpp"
  )
add_library(imgui ${imgui_src})
target_include_directories(imgui INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)

# fmtlib
execute_process(COMMAND git submodule update --init -- external/fmt
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/fmt)

# Guideline Support library
execute_process(COMMAND git submodule update --init -- external/GSL
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/GSL)

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW examples")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW tests")
execute_process(COMMAND git submodule update --init -- external/glfw
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)

# Backward
execute_process(COMMAND git submodule update --init -- external/backward-cpp
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(Backward_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/backward-cpp)
add_subdirectory(${Backward_DIR})
find_package(Backward)

if(OTTO_BUILD_DOCS)
  execute_process(COMMAND git submodule update --init -- external/standardese
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  set(standardese_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/standardese)
  set(STANDARDESES_BUILD_TEST OFF CACHE BOOL "Build standardese tests")
  add_subdirectory(${standardese_DIR})
  include(${standardese_DIR}/standardese-config.cmake)
endif()
