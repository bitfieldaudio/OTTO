cmake_minimum_required (VERSION 2.6)
project (Tapedeck)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

find_package(PkgConfig REQUIRED)
add_executable(tapedeck ${PROJECT_SOURCE_DIR}/src/main.cpp)

function(target_add_lib name)
  pkg_check_modules(LIB123 REQUIRED ${name})
  target_link_libraries(tapedeck ${LIB123_LIBRARIES})
  target_include_directories(tapedeck PUBLIC ${LIB123_INCLUDE_DIRS})
  target_compile_options(tapedeck PUBLIC ${LIB123_CFLAGS_OTHER})
endfunction(target_add_lib)

target_add_lib(gtk+-3.0)
target_add_lib(jack)
target_add_lib(cairo)
