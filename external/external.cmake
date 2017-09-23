set(CMAKE_CXX_STANDARD 17)

# General purpose externals
file(GLOB_RECURSE external_src
  "${CMAKE_CURRENT_SOURCE_DIR}/external/src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/src/*.cpp"
)
add_library(external ${external_src})
target_include_directories(external PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/include)
set_target_properties(external PROPERTIES LINKER_LANGUAGE CXX)

# Nanovg
execute_process(COMMAND git submodule update --init -- external/nanovg
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE nanovg_src "${CMAKE_CURRENT_SOURCE_DIR}/external/nanovg/src/*.c")
add_library(nanovg ${nanovg_src})
target_include_directories(nanovg INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/external/nanovg/src)
target_link_libraries(nanovg INTERFACE GLESv2)

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
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
execute_process(COMMAND git submodule update --init -- external/glfw
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)

# Static math
execute_process(COMMAND git submodule update --init -- external/constexpr
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_library(constexpr INTERFACE)
target_include_directories(constexpr INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/external/constexpr/src/include)
