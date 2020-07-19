set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic -Wno-unused-function")
elseif(${CMAKE_CXX_COMPILER_ID} EQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pedantic -Wno-unused-function")
endif()

# General purpose externals
file(GLOB_RECURSE external_src
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
add_library(external ${external_src})
target_include_directories(external SYSTEM PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (APPLE)
  find_library(CORE_FOUNDATION CoreFoundation)
  target_link_libraries(external ${CORE_FOUNDATION})
endif()

# Download External Dependencies via CPM
CPMAddPackage(
  NAME fmt
  GITHUB_REPOSITORY fmtlib/fmt
  GIT_TAG 6.2.0
)

# We're on version v1.0.0-289-g1999b48 which is not officially tagged in Github
# so we're going to use the SHA directly.
CPMAddPackage(
  NAME GSL
  GITHUB_REPOSITORY microsoft/GSL
  GIT_TAG 1999b48a519196711f0d03af3b7eedd49fcc6db3
)

# We're on version v0.3.0-123-gff67c1a which is not officially tagged in Github
# so we're going to use the SHA directly.
CPMAddPackage(
  NAME Choreograph
  GITHUB_REPOSITORY topisani/Choreograph
  GIT_TAG ff67c1a
  DOWNLOAD_ONLY YES
)
if (Choreograph_ADDED)
  file(GLOB_RECURSE choreograph_sources ${Choreograph_SOURCE_DIR}/src/**.cpp)
  add_library(choreograph ${choreograph_sources})
  target_include_directories(choreograph
    SYSTEM PUBLIC
      $<BUILD_INTERFACE:${Choreograph_SOURCE_DIR}/src>
  )
endif()

CPMAddPackage(
  NAME gamma
  GITHUB_REPOSITORY LancePutnam/Gamma
  GIT_TAG 6c2ef03734c44f32c8cc02f63d528e96c980ed23
  DOWNLOAD_ONLY YES
)
if (gamma_ADDED)
  execute_process(COMMAND mkdir -p "${CMAKE_CURRENT_BINARY_DIR}/include")
  execute_process(COMMAND ln -sf "${gamma_SOURCE_DIR}/Gamma" "${CMAKE_CURRENT_BINARY_DIR}/include/Gamma")
  file(GLOB_RECURSE gamma_src "${gamma_SOURCE_DIR}/src/*.cpp")
  list(REMOVE_ITEM gamma_src 
    "${gamma_SOURCE_DIR}/src/SoundFile.cpp"
    "${gamma_SOURCE_DIR}/src/AudioIO.cpp")
  add_library(gamma ${gamma_src})
  target_include_directories(gamma SYSTEM PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include")
endif()

CPMAddPackage(
  NAME nanovg
  GITHUB_REPOSITORY memononen/nanovg
  GIT_TAG 2bead03bea43b2418060aaa154f972829995e663 
  DOWNLOAD_ONLY YES
)
if (nanovg_ADDED) 
  file(GLOB_RECURSE nanovg_src "${nanovg_SOURCE_DIR}/src/*.c")
  add_library(nanovg ${nanovg_src})
  target_include_directories(nanovg SYSTEM INTERFACE "${nanovg_SOURCE_DIR}/src")
  if (APPLE)
    find_package(OpenGL)
    target_include_directories(nanovg SYSTEM INTERFACE ${OPENGL_INCLUDE_DIR})
    target_link_libraries(nanovg INTERFACE ${OPENGL_LIBRARIES})
  endif()
endif()

CPMAddPackage(
  NAME nlohmann_json
  GITHUB_REPOSITORY nlohmann/json
  VERSION 3.8.0
  DOWNLOAD_ONLY YES
  GIT_SHALLOW ON
)

if (nlohmann_json_ADDED)
  add_library(nlohmann_json INTERFACE)
  target_include_directories(nlohmann_json SYSTEM INTERFACE "${nlohmann_json_SOURCE_DIR}/include")
  # TODO: Remove this when we no longer depend on better_enum
  target_include_directories(nlohmann_json SYSTEM INTERFACE "${nlohmann_json_SOURCE_DIR}/include/nlohmann")
endif()

CPMAddPackage(
  NAME doctest
  GITHUB_REPOSITORY onqtam/doctest
  GIT_TAG 2.3.2
)

CPMAddPackage(
  NAME nanobench
  VERSION 4.0.0
  GITHUB_REPOSITORY martinus/nanobench
  DOWNLOAD_ONLY YES
)

if (nanobench_ADDED) 
  add_library(nanobench INTERFACE)
  target_include_directories(nanobench SYSTEM INTERFACE "${nanobench_SOURCE_DIR}/src/include")
endif()

CPMAddPackage(
  NAME magic_enum
  GITHUB_REPOSITORY Neargye/magic_enum
  VERSION 0.6.6
)

CPMAddPackage(
  NAME concurrentqueue
  VERSION 1.0.1
  GITHUB_REPOSITORY cameron314/concurrentqueue
  DOWNLOAD_ONLY YES
)

if (concurrentqueue_ADDED) 
  add_library(concurrentqueue INTERFACE)
  target_include_directories(concurrentqueue SYSTEM INTERFACE "${concurrentqueue_SOURCE_DIR}")
endif()
