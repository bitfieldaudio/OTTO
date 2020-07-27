set(CMAKE_CXX_STANDARD 20)

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

find_package(PkgConfig) 

pkg_check_modules(SKIA IMPORTED_TARGET skia)

if (SKIA_FOUND)
  message("Found system skia")
  add_library(skia INTERFACE)
  target_link_libraries(skia INTERFACE PkgConfig::SKIA)
else()
  CPMAddPackage(
    NAME skia
    GIT_REPOSITORY https://skia.googlesource.com/skia.git
    GIT_TAG c8ae494401bc38b5d0d9c99c962d207f4668ad63
    DOWNLOAD_ONLY YES
  )

  if (skia_ADDED)
    set(skia_LIB_LOCATION "${skia_SOURCE_DIR}/out/Static/libskia.a")
    set(skia_ARGS "\
  is_debug=true \
  paragraph_gms_enabled=false \
  paragraph_tests_enabled=false \
  skia_enable_android_utils=false \
  skia_enable_api_available_macro=true \
  skia_enable_ccpr=true \
  skia_enable_direct3d_debug_layer=false \
  skia_enable_discrete_gpu=true \
  skia_enable_fontmgr_FontConfigInterface=true \
  skia_enable_fontmgr_android=false \
  skia_enable_fontmgr_custom_directory=true \
  skia_enable_fontmgr_custom_embedded=true \
  skia_enable_fontmgr_custom_empty=true \
  skia_enable_fontmgr_fontconfig=true \
  skia_enable_gpu=true \
  skia_enable_gpu_debug_layers=true \
  skia_enable_nvpr=false \
  skia_enable_particles=false \
  skia_enable_pdf=false \
  skia_enable_skottie=false \
  skia_enable_skparagraph=true \
  skia_enable_skrive=false \
  skia_enable_skshaper=false \
  skia_enable_sksl_interpreter=false \
  skia_enable_skvm_jit=false \
  skia_enable_spirv_validation=false \
  skia_enable_tools=false \
  skia_enable_vulkan_debug_layers=false \
  skia_use_dng_sdk=false \
  skia_use_expat=false \
  skia_use_fontconfig=true \
  skia_use_freetype=true \
  skia_use_gl=true \
  skia_use_harfbuzz=false \
  skia_use_icu=false \
  skia_use_libgifcodec=false \
  skia_use_libheif=false \
  skia_use_libjpeg_turbo_decode=false \
  skia_use_libjpeg_turbo_encode=false \
  skia_use_libpng_decode=true \
  skia_use_libpng_encode=false \
  skia_use_libwebp_decode=false \
  skia_use_libwebp_encode=false \
  skia_use_lua=false \
  skia_use_piex=false \
  skia_use_sfntly=false \
  skia_use_system_freetype2=true \
  skia_use_x11=false \
  skia_use_xps=false \
  skia_use_zlib=false")

    message("Downloading skia third party dependencies (might take a while)...")
    execute_process(
      COMMAND python tools/git-sync-deps
      WORKING_DIRECTORY "${skia_SOURCE_DIR}"  
    )
    message("Generating skia cmake project...")
    execute_process(
      COMMAND bin/gn gen out/config --ide=json --json-ide-script=../../gn/gn_to_cmake.py --args=${skia_ARGS}
      WORKING_DIRECTORY "${skia_SOURCE_DIR}"  
    )
    add_definitions("-Wno-unknown-warning-option -Wno-gnu-zero-variadic-macro-arguments")
    set(CMAKE_CXX_STANDARD 17)
    add_subdirectory("${skia_SOURCE_DIR}/out/config" "${skia_BINARY_DIR}" EXCLUDE_FROM_ALL)
    target_include_directories(skia PUBLIC SYSTEM "${skia_SOURCE_DIR}/")
    target_include_directories(skia PUBLIC SYSTEM "${skia_SOURCE_DIR}/include/core")
    target_include_directories(skia PUBLIC SYSTEM "${skia_SOURCE_DIR}/include/gpu")
  endif()
endif()
