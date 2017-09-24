set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE sources ${TOP-1_SOURCE_DIR}/test/*.cpp)

# Executable
add_executable(top-1_test ${sources})
target_link_libraries(top-1_test PUBLIC top-1)
target_include_directories(top-1_test PUBLIC ${TOP-1_SOURCE_DIR}/test)
set_target_properties(top-1_test PROPERTIES OUTPUT_NAME test)
