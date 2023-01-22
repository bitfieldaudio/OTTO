set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE headers "${OTTO_SOURCE_DIR}/src/*.hpp")
file(GLOB_RECURSE sources "${OTTO_SOURCE_DIR}/src/*.cpp")

find_package (Threads)
# Library
add_library(otto_src OBJECT ${sources})
target_include_directories(otto_src PUBLIC ${OTTO_SOURCE_DIR}/src)
target_link_libraries(otto_src PUBLIC ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})

# Executable
add_executable(otto_exec ${OTTO_SOURCE_DIR}/boards/${OTTO_BOARD}/src/main.cpp)
target_link_libraries(otto_exec PUBLIC otto_src)
set_target_properties(otto_exec PROPERTIES OUTPUT_NAME otto)

add_subdirectory(${OTTO_EXTERNAL_DIR} ${OTTO_BINARY_DIR}/external)

# This updates configurations and includes board specific files
otto_include_board(${OTTO_BOARD})
otto_add_definitions(otto_src)
otto_add_definitions(otto_exec)

if (NOT OTTO_USE_LIBCXX)
  target_link_libraries(otto_src PUBLIC atomic)
endif()

target_link_libraries(otto_src PUBLIC external)
target_link_libraries(otto_src PUBLIC fmt)
target_link_libraries(otto_src PUBLIC gamma)
target_link_libraries(otto_src PUBLIC choreograph)
target_link_libraries(otto_src PUBLIC nlohmann_json)
target_link_libraries(otto_src PUBLIC spdlog)
target_link_libraries(otto_src PUBLIC nanobench)
target_link_libraries(otto_src PUBLIC magic_enum)
target_link_libraries(otto_src PUBLIC concurrentqueue)
target_link_libraries(otto_src PUBLIC skia)
target_link_libraries(otto_src PUBLIC function2)
target_link_libraries(otto_src PUBLIC argparse)
target_link_libraries(otto_src PUBLIC otto_boost)
target_link_libraries(otto_src PUBLIC yamc)
target_link_libraries(otto_src PUBLIC Linenoise)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OTTO_CXX_FLAGS}")

# Docs  
if (OTTO_BUILD_DOCS)    
# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${OTTO_SOURCE_DIR}/doxygen/Doxyfile.in)
    set(DOXYGEN_OUT ${OTTO_BINARY_DIR}/doxygen/Doxyfile)
        
    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${OTTO_SOURCE_DIR}/doxygen
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)# check if Doxygen is installed
endif()
