set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE headers ${TOP-1_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE sources ${TOP-1_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM sources ${TOP-1_SOURCE_DIR}/src/main.cpp)

find_package (Threads)
# Library
add_library(top-1 ${sources} ${BACKWARD_ENABLE})
add_backward(top-1)
target_link_libraries(top-1 PUBLIC external)
target_link_libraries(top-1 PUBLIC nanocanvas)
target_link_libraries(top-1 PUBLIC GSL)
target_link_libraries(top-1 PUBLIC fmt)
target_link_libraries(top-1 PUBLIC glfw)
target_link_libraries(top-1 PUBLIC jack)
target_link_libraries(top-1 PUBLIC ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(top-1 PUBLIC Backward::Backward)
target_include_directories(top-1 PUBLIC ./)

if (NOT APPLE)
  # Currently you have to set these manually on osx.
  # See https://github.com/topisani/TOP-1/issues/13
  target_link_libraries(top-1 PUBLIC stdc++fs)
  target_link_libraries(top-1 PUBLIC atomic)
endif()

target_link_libraries(top-1 PUBLIC imgui)
target_compile_definitions(top-1 PUBLIC TOP1_DEBUG_UI)

# Executable
add_executable(top-1_exec ${TOP-1_SOURCE_DIR}/src/main.cpp ${BACKWARD_ENABLE})
target_link_libraries(top-1_exec PUBLIC top-1)
set_target_properties(top-1_exec PROPERTIES OUTPUT_NAME top-1)
