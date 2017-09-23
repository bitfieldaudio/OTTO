set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE headers ${TOP-1_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE sources ${TOP-1_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM sources ${TOP-1_SOURCE_DIR}/src/main.cpp)

find_package (Threads)
# Library
add_library(top-1 ${sources})
target_link_libraries(top-1 PUBLIC external)
target_link_libraries(top-1 PUBLIC nanocanvas)
target_link_libraries(top-1 PUBLIC GSL)
target_link_libraries(top-1 PUBLIC fmt)
target_link_libraries(top-1 PUBLIC glfw)
target_link_libraries(top-1 PUBLIC jack)
target_link_libraries(top-1 PUBLIC stdc++fs)
target_link_libraries(top-1 PUBLIC atomic)
target_link_libraries(top-1 PUBLIC ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(top-1 PUBLIC ./)

# Executable
add_executable(top-1_exec ${TOP-1_SOURCE_DIR}/src/main.cpp)
target_link_libraries(top-1_exec PUBLIC top-1)
set_target_properties(top-1_exec PROPERTIES OUTPUT_NAME top-1)
