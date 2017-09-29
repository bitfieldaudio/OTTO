set(CMAKE_CXX_STANDARD 17)

# General purpose externals (header only only)
add_library(external INTERFACE)
target_include_directories(external INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/external/include)

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
  target_link_libraries(nanovg INTERFACE GLESv2)
endif()

# NanoCanvas
execute_process(COMMAND git submodule update --init -- external/NanoCanvas
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE nanocanvas_src "${CMAKE_CURRENT_SOURCE_DIR}/external/NanoCanvas/src/*.cpp")
add_library(nanocanvas ${nanocanvas_src})
target_link_libraries(nanocanvas nanovg)
target_include_directories(nanocanvas INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/external/NanoCanvas/src)

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
