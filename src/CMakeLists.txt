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
target_link_libraries(otto PUBLIC jack)
target_link_libraries(otto PUBLIC imgui)
target_link_libraries(otto PUBLIC ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(otto PUBLIC ./)

if (NOT OTTO_USE_LIBCXX)
  target_link_libraries(otto PUBLIC atomic)
endif()

if (RPI)
  link_directories("/opt/vc/lib")
  set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/opt/vc/lib")
  find_library(BCM_HOST bcm_host)
  find_library(BCM_EGL brcmEGL)
  find_library(BCM_GLES brcmGLESv2)
  target_link_libraries(otto PUBLIC ${BCM_HOST})
  target_link_libraries(otto PUBLIC ${BCM_EGL})
  target_link_libraries(otto PUBLIC ${BCM_GLES})
  target_include_directories(otto PUBLIC "/opt/vc/include")
else ()
  target_link_libraries(otto PUBLIC glfw)
endif ()

# Executable
add_executable(otto_exec ${OTTO_SOURCE_DIR}/src/main.cpp ${BACKWARD_ENABLE})
target_link_libraries(otto_exec PUBLIC otto)
set_target_properties(otto_exec PROPERTIES OUTPUT_NAME otto)

