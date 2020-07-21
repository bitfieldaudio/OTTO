# Generate gl3w files
include("${OTTO_EXTERNAL_DIR}/gl3w_gen.cmake")
gl3w_gen("${OTTO_BINARY_DIR}/external/")
target_sources(otto_src PRIVATE "${OTTO_BINARY_DIR}/external/src/gl3w.c")
target_include_directories(otto_src PUBLIC "${OTTO_BINARY_DIR}/external/include")

# GLFW
CPMFindPackage(
  NAME glfw3
  GITHUB_REPOSITORY glfw/glfw
  GIT_TAG 3.3.2
  OPTIONS
    "GLFW_BUILD_TESTS OFF"
    "GLFW_BUILD_EXAMPLES OFF"
    "GLFW_BULID_DOCS OFF"
)
target_link_libraries(otto_src PUBLIC glfw)
