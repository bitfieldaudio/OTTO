set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic -Wno-unused-function")
elseif(${CMAKE_CXX_COMPILER_ID} EQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic -Wno-unused-function")
endif()

# Generate gl3w files
include("${CMAKE_CURRENT_SOURCE_DIR}/gl3w_gen.cmake")
gl3w_gen("${CMAKE_CURRENT_SOURCE_DIR}/")

# General purpose externals (header only only)
file(GLOB_RECURSE external_src
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  )
add_library(external ${external_src})
target_include_directories(external SYSTEM PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Nanovg
execute_process(COMMAND git submodule update --init -- nanovg WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE nanovg_src "${CMAKE_CURRENT_SOURCE_DIR}/nanovg/src/*.c")
add_library(nanovg ${nanovg_src})
target_include_directories(nanovg SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/nanovg/src)

# Link to the OpenGL framework on OSX
if (APPLE)
  find_package(OpenGL)
  target_include_directories(nanovg SYSTEM INTERFACE ${OPENGL_INCLUDE_DIR})
  target_link_libraries(nanovg INTERFACE ${OPENGL_LIBRARIES})
endif()

# NanoCanvas
execute_process(COMMAND git submodule update --init -- NanoCanvas WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE nanocanvas_src "${CMAKE_CURRENT_SOURCE_DIR}/NanoCanvas/src/*.cpp")
add_library(nanocanvas ${nanocanvas_src})
target_link_libraries(nanocanvas nanovg)
target_include_directories(nanocanvas SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/NanoCanvas/src)

# Imgui
execute_process(COMMAND git submodule update --init -- imgui WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB imgui_src
  "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp"
  )
add_library(imgui ${imgui_src})
target_include_directories(imgui SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

# fmtlib
execute_process(COMMAND git submodule update --init -- fmt WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fmt)

# Guideline Support library
execute_process(COMMAND git submodule update --init -- GSL WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GSL)

if (RPI)
else (RPI)
  # GLFW
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW examples")
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW tests")
  execute_process(COMMAND git submodule update --init -- glfw WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
endif (RPI)
