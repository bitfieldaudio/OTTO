# Generate gl3w files
include("${OTTO_EXTERNAL_DIR}/gl3w_gen.cmake")
gl3w_gen("${OTTO_EXTERNAL_DIR}/")

# GLFW
find_package(glfw3)
if (glfw3_FOUND)
    message("Using system GLFW")
    target_link_libraries(glfw INTERFACE dl)
else() 
    message("GLFW not found, building from source")
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW examples")
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW tests")
    execute_process(COMMAND git submodule update --init -- glfw WORKING_DIRECTORY ${OTTO_EXTERNAL_DIR})
    add_subdirectory(${OTTO_EXTERNAL_DIR}/glfw ${OTTO_BINARY_DIR}/external/glfw)
endif()

target_link_libraries(otto PUBLIC glfw)
