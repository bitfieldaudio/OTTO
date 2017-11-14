set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE headers ${OTTO_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE sources ${OTTO_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM sources ${OTTO_SOURCE_DIR}/src/main.cpp)

find_package (Threads)
# Library
add_library(otto ${sources} ${BACKWARD_ENABLE})
target_link_libraries(otto PUBLIC external)
target_link_libraries(otto PUBLIC nanocanvas)
target_link_libraries(otto PUBLIC GSL)
target_link_libraries(otto PUBLIC fmt)
target_link_libraries(otto PUBLIC glfw)
target_link_libraries(otto PUBLIC jack)
target_link_libraries(otto PUBLIC ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(otto PUBLIC ./)

if (OTTO_USE_LIBCXX)
  target_link_libraries(otto PUBLIC c++experimental)
else()
  target_link_libraries(otto PUBLIC stdc++fs)
  target_link_libraries(otto PUBLIC atomic)
endif()

target_link_libraries(otto PUBLIC imgui)
target_compile_definitions(otto PUBLIC OTTO_DEBUG_UI)

# Executable
add_executable(otto_exec ${OTTO_SOURCE_DIR}/src/main.cpp ${BACKWARD_ENABLE})
target_link_libraries(otto_exec PUBLIC otto)
set_target_properties(otto_exec PROPERTIES OUTPUT_NAME otto)


# Docs
if (OTTO_BUILD_DOCS)
  standardese_generate(otto CONFIG ${OTTO_SOURCE_DIR}/.standardese
    INCLUDE_DIRECTORY ${otto_includedirs}
    INPUT ${headers})
endif()
