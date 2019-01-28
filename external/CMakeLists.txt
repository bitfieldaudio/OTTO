set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic -Wno-unused-function")
elseif(${CMAKE_CXX_COMPILER_ID} EQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic -Wno-unused-function")
endif()

# General purpose externals
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
  find_library(CORE_FOUNDATION CoreFoundation)
  target_link_libraries(external ${CORE_FOUNDATION})
endif()

# NanoCanvas
execute_process(COMMAND git submodule update --init -- NanoCanvas WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE nanocanvas_src "${CMAKE_CURRENT_SOURCE_DIR}/NanoCanvas/src/*.cpp")
add_library(nanocanvas ${nanocanvas_src})
target_link_libraries(nanocanvas nanovg)
target_include_directories(nanocanvas SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/NanoCanvas/src)

# fmtlib
execute_process(COMMAND git submodule update --init -- fmt WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fmt)

# Guideline Support library
execute_process(COMMAND git submodule update --init -- GSL WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GSL)

# Ranges V3
execute_process(COMMAND git submodule update --init -- range-v3 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_library(range-v3 INTERFACE)
target_include_directories(range-v3 SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/range-v3/include)

# Gamma
execute_process(COMMAND git submodule update --init -- Gamma WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(COMMAND ln -s "${CMAKE_CURRENT_SOURCE_DIR}/Gamma/Gamma" "${CMAKE_CURRENT_SOURCE_DIR}/include/Gamma")
file(GLOB_RECURSE gamma_src "${CMAKE_CURRENT_SOURCE_DIR}/Gamma/src/*.cpp")
list(REMOVE_ITEM gamma_src 
  "${CMAKE_CURRENT_SOURCE_DIR}/Gamma/src/SoundFile.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Gamma/src/AudioIO.cpp")
add_library(gamma ${gamma_src})
target_include_directories(gamma PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Gamma)
