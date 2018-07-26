# Generate gl3w files
if(NOT APPLE)
    include("${OTTO_EXTERNAL_DIR}/gl3w_gen.cmake")
    gl3w_gen("${OTTO_EXTERNAL_DIR}/")
endif()

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW examples")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW tests")
execute_process(COMMAND git submodule update --init -- glfw WORKING_DIRECTORY ${OTTO_EXTERNAL_DIR})
add_subdirectory(${OTTO_EXTERNAL_DIR}/glfw ${OTTO_BINARY_DIR}/external/glfw)

target_link_libraries(otto PUBLIC glfw)
