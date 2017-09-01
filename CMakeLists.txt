cmake_minimum_required (VERSION 3.1)
project (TOP-1)
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
target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR}/tests)

target_link_libraries(top-1 libtop-1)
target_link_libraries(tests libtop-1)

target_link_libraries(libtop-1 pthread)
target_link_libraries(libtop-1 dl)

include_directories("src")
include_directories(SYSTEM "include")
include_directories(SYSTEM "include/nanovg")
include_directories(SYSTEM "include/nanocanvas")

add_library(external-libs STATIC ${TOP-1_LIBS})
set_target_properties(external-libs PROPERTIES COMPILE_FLAGS "-w -x c++ -std=c++1z")
target_link_libraries(libtop-1 external-libs)

# use c++17 for TOP-1
set_target_properties(libtop-1 PROPERTIES COMPILE_FLAGS "-x c++ -std=c++1z -Wno-c++14-compat-pedantic")
set_target_properties(top-1 PROPERTIES COMPILE_FLAGS "-x c++ -std=c++1z -Wno-c++14-compat-pedantic")
set_target_properties(tests PROPERTIES COMPILE_FLAGS "-x c++ -std=c++1z  -Wno-c++14-compat-pedantic") 

# pkg-config find libs
function(target_add_lib name)
  pkg_check_modules(${name} REQUIRED ${name})
  target_link_libraries(libtop-1 ${${name}_LIBRARIES})
  target_include_directories(libtop-1 SYSTEM PUBLIC ${${name}_INCLUDE_DIRS})
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
enable_cxx_compiler_flag_if_supported("-Wall")

# Generate documentation
file(GLOB_RECURSE DOC_FILES
  "src/*.hpp"
)

set(CLDOC "" CACHE STRING "User specified '/path/to/cldoc'")
set(CLDOC /usr/local/bin/cldoc)
if(CLDOC STREQUAL "")
	find_program(CLDOC cldoc)
elseif(NOT EXISTS ${CLDOC})
	message(FATAL_ERROR "CLDOC was set to '${CLDOC}' but does not exist")
endif()

if(NOT DOCS_OUTPUT_DIR)
	set(DOCS_OUTPUT_DIR "docs" CACHE STRING "Generated documentation output directory" FORCE)
endif()

if(NOT DOCS_DIR)
	set(DOCS_DIR "doc-src" CACHE STRING "Location of external documentation files to be merged in" FORCE)
endif()

if(NOT ${CLDOC} STREQUAL "CLDOC-NOTFOUND")
  if(NOT ${DOCS_DIR} STREQUAL "")
  	set(CLDOC_MERGE "--merge ${DOCS_DIR}")
  else()
  	set(CLDOC_MERGE "")
  endif()

  add_custom_target(docs COMMAND
    ${CLDOC} generate
    ${CMAKE_CXX_FLAGS}
    -x c++ -std=c++1z
    -I ./include -I ./include/nanovg
    -I${PROJECT_SOURCE_DIR}/src
    --
    --output=${DOCS_OUTPUT_DIR}
    ${DOC_FILES}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

  set_target_properties(docs PROPERTIES
    EXCLUDE_FROM_ALL 1
    EXCLUDE_FROM_DEFAULT_BUILD 1
  )

  add_custom_target(serve_docs COMMAND
    ${CLDOC} serve -- ${DOCS_OUTPUT_DIR}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

  set_target_properties(docs PROPERTIES
    EXCLUDE_FROM_ALL 1
    EXCLUDE_FROM_DEFAULT_BUILD 1
  )

  add_dependencies(serve_docs docs)
else()
  message(STATUS
    "Documentation will not be generated"
  )
endif()
