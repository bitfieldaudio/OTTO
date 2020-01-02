set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE sources ${OTTO_SOURCE_DIR}/test/*.cpp)

# Executable
add_executable(otto_test ${sources})
target_link_libraries(otto_test PUBLIC otto)
target_include_directories(otto_test PUBLIC ${OTTO_SOURCE_DIR}/test)
set_target_properties(otto_test PROPERTIES OUTPUT_NAME test)

include("${OTTO_SOURCE_DIR}/cmake/doctest_force_link_static_lib_in_target.cmake")
doctest_force_link_static_lib_in_target(otto_test otto)

otto_add_definitions(otto_test)
