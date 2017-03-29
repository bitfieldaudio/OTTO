cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 14)
project (Tapedeck)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

find_package(PkgConfig REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(GLOB_RECURSE TAPEDECK_SRC
    "src/*.cpp"
)

add_executable(tapedeck ${TAPEDECK_SRC})

target_link_libraries(tapedeck pthread)
target_link_libraries(tapedeck dl)
include_directories("include")

function(target_add_lib name)
  pkg_check_modules(${name} REQUIRED ${name})
  target_link_libraries(tapedeck ${${name}_LIBRARIES})
  target_include_directories(tapedeck PUBLIC ${${name}_INCLUDE_DIRS})
  target_compile_options(tapedeck PUBLIC ${${name}_CFLAGS_OTHER})
endfunction(target_add_lib)

target_add_lib(jack)
target_add_lib(gtk+-3.0)
target_add_lib(cairo)
target_add_lib(sndfile)
