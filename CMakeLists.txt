cmake_minimum_required (VERSION 3.1)
project (TOP-1)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(PkgConfig REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(GLOB_RECURSE TOP-1_SRC
  "src/*.cpp"
)
list(REMOVE_ITEM TOP-1_SRC ${CMAKE_SOURCE_DIR}/src/main.cpp)

file(GLOB_RECURSE TOP-1_LIBS
  "lib/*.cpp"
  "lib/*.c"
  "lib/*.cc"
)

file(GLOB_RECURSE TOP-1_TESTS
  "tests/*.cpp"
)

add_executable(top-1 ${CMAKE_SOURCE_DIR}/src/main.cpp)
add_library(libtop-1 ${TOP-1_SRC})
add_executable(tests ${TOP-1_TESTS})

add_custom_target(check COMMAND tests)

target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(top-1 libtop-1)
target_link_libraries(tests libtop-1)

target_link_libraries(libtop-1 pthread)
target_link_libraries(libtop-1 dl)

include_directories("include/nanovg")
include_directories("include/nanocanvas")
include_directories("include")

add_library(external-libs STATIC ${TOP-1_LIBS})
target_link_libraries(libtop-1 external-libs)

# pkg-config find libs
function(target_add_lib name)
  pkg_check_modules(${name} REQUIRED ${name})
  target_link_libraries(libtop-1 ${${name}_LIBRARIES})
  target_include_directories(libtop-1 PUBLIC ${${name}_INCLUDE_DIRS})
  target_compile_options(libtop-1 PUBLIC ${${name}_CFLAGS_OTHER})
endfunction(target_add_lib)

# DEPENDENCIES

target_add_lib(jack)
target_add_lib(glfw3)
target_add_lib(gl)

include(CheckCXXCompilerFlag)

function(enable_cxx_compiler_flag_if_supported flag)
    string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
    if(flag_already_set EQUAL -1)
        check_cxx_compiler_flag("${flag}" flag_supported)
        if(flag_supported)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
        endif()
    endif()
endfunction()

# example usage
#enable_cxx_compiler_flag_if_supported("-Wall")
#enable_cxx_compiler_flag_if_supported("-Wextra")
#enable_cxx_compiler_flag_if_supported("-pedantic")

# add_custom_command(TARGET tapedeck
#   PRE_BUILD
#   COMMAND "./compile-faust.sh"
#   WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
