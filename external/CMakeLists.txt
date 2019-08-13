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

# fmtlib
execute_process(COMMAND git submodule update --init -- fmt WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fmt)

# Guideline Support library
execute_process(COMMAND git submodule update --init -- GSL WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GSL)

# Gamma
execute_process(COMMAND git submodule update --init -- Gamma WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(COMMAND mkdir -p "${CMAKE_CURRENT_BINARY_DIR}/include")
execute_process(COMMAND rm "${CMAKE_CURRENT_BINARY_DIR}/include/Gamma")
execute_process(COMMAND ln -s "${CMAKE_CURRENT_SOURCE_DIR}/Gamma/Gamma" "${CMAKE_CURRENT_BINARY_DIR}/include/Gamma")
file(GLOB_RECURSE gamma_src "${CMAKE_CURRENT_SOURCE_DIR}/Gamma/src/*.cpp")
list(REMOVE_ITEM gamma_src 
  "${CMAKE_CURRENT_SOURCE_DIR}/Gamma/src/SoundFile.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/Gamma/src/AudioIO.cpp")
add_library(gamma ${gamma_src})
target_include_directories(gamma SYSTEM PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include")

# foonathan/array
execute_process(COMMAND git submodule update --init -- foonathan_array WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_library(foonathan_array INTERFACE)
target_include_directories(foonathan_array SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/foonathan_array/include")

# foonathan/array
execute_process(COMMAND git submodule update --init -- foonathan_type_safe WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
execute_process(COMMAND git submodule update --init -- external/debug_assert WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/foonathan_type_safe)
add_library(foonathan_type_safe INTERFACE)
target_include_directories(foonathan_type_safe SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/foonathan_type_safe/include")
target_include_directories(foonathan_type_safe SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/foonathan_type_safe/external/debug_assert")

# Choreograph
execute_process(COMMAND git submodule update --init -- choreograph WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE choreograph_src "${CMAKE_CURRENT_SOURCE_DIR}/choreograph/src/**.cpp")
add_library(choreograph ${choreograph_src})
target_include_directories(choreograph SYSTEM PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/choreograph/src")
