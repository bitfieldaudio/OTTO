set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE sources ${OTTO_SOURCE_DIR}/test/*.cpp)

# Executable
add_executable(otto_test ${sources})
target_link_libraries(otto_test PUBLIC otto_src)
target_include_directories(otto_test PUBLIC ${OTTO_SOURCE_DIR}/test)
set_target_properties(otto_test PROPERTIES OUTPUT_NAME test)

otto_add_definitions(otto_test)
