set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE headers ${OTTO_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE sources ${OTTO_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM sources ${OTTO_SOURCE_DIR}/src/main.cpp)

find_package (Threads)
# Library
add_library(otto ${sources} ${BACKWARD_ENABLE})
target_link_libraries(otto PUBLIC ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(otto PUBLIC ./)

# This updates configurations and includes board specific files
otto_include_board(${OTTO_BOARD})
otto_add_definitions(otto)

if (NOT OTTO_USE_LIBCXX)
  target_link_libraries(otto PUBLIC atomic)
endif()

# Executable
add_executable(otto_exec ${OTTO_SOURCE_DIR}/src/main.cpp ${BACKWARD_ENABLE})
target_link_libraries(otto_exec PUBLIC otto)
set_target_properties(otto_exec PROPERTIES OUTPUT_NAME otto)

add_subdirectory(${OTTO_EXTERNAL_DIR} ${OTTO_BINARY_DIR}/external)
target_link_libraries(otto PUBLIC external)
target_link_libraries(otto PUBLIC nanocanvas)
target_link_libraries(otto PUBLIC GSL)
target_link_libraries(otto PUBLIC fmt)
target_link_libraries(otto PUBLIC imgui)
target_link_libraries(otto PUBLIC range-v3)
target_link_libraries(otto PUBLIC tiny-process-library)

# Enable warnings for local code
if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -Wpedantic -Wno-c++14-compat -Wno-psabi -Wno-unknown-pragmas")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -Wpedantic \
-Wno-c++11-compat -Wno-c++98-compat -Wno-c++14-compat -Wc++17-compat \
-Wno-shadow-field-in-constructor \
-Wno-documentation-unknown-command \
-Wno-unknown-pragmas \
")
endif()

