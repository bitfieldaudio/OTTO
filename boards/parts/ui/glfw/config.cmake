# Generate gl3w files
include("${OTTO_EXTERNAL_DIR}/gl3w_gen.cmake")
gl3w_gen("${OTTO_BINARY_DIR}/external/")
target_sources(external PRIVATE "${OTTO_BINARY_DIR}/external/src/gl3w.c")
target_include_directories(external PUBLIC "${OTTO_BINARY_DIR}/external/include")

# GLFW
find_package(glfw3 QUIET)
if (glfw3_FOUND)
    message("Using system GLFW")
    #pkg_search_module(GLFW REQUIRED glfw3)
    include_directories(${GLFW_INCLUDE_DIRS})
    target_link_libraries(otto_src ${GLFW_LIBRARIES})
    target_link_libraries(otto_src PUBLIC dl)
else() 
    message("GLFW not found, building from source")
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW examples")
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW tests")
    execute_process(COMMAND git submodule update --init -- glfw WORKING_DIRECTORY ${OTTO_EXTERNAL_DIR})
    add_subdirectory(${OTTO_EXTERNAL_DIR}/glfw ${OTTO_BINARY_DIR}/external/glfw)
endif()

target_link_libraries(otto_src PUBLIC glfw)
