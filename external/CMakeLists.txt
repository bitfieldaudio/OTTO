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
CPMAddPackage("gh:fmtlib/fmt#8.0.1")
CPMAddPackage("gh:catchorg/Catch2@3.2.1")
CPMAddPackage("gh:Neargye/magic_enum@0.7.2")
CPMAddPackage("gh:Naios/function2#4.1.0")
CPMAddPackage("gh:gabime/spdlog@1.9.2") 
CPMAddPackage("gh:p-ranav/argparse@2.9") 
CPMAddPackage("gh:topisani/choreograph@0.5.0")
CPMAddPackage("gh:nlohmann/json@3.11.2")
CPMAddPackage("gh:GerHobbelt/linenoise#9509586af67aaa60faf0a87066761ab741b98f61")

CPMAddPackage(
  NAME gamma
  GITHUB_REPOSITORY LancePutnam/Gamma
  GIT_TAG 6c2ef03734c44f32c8cc02f63d528e96c980ed23
  DOWNLOAD_ONLY YES
)
if (gamma_ADDED)
  execute_process(COMMAND mkdir -p "${CMAKE_CURRENT_BINARY_DIR}/include")
  execute_process(COMMAND ln -sf "${gamma_SOURCE_DIR}/Gamma" "${CMAKE_CURRENT_BINARY_DIR}/include/")
  file(GLOB_RECURSE gamma_src "${gamma_SOURCE_DIR}/src/*.cpp")
  list(REMOVE_ITEM gamma_src 
    #"${gamma_SOURCE_DIR}/src/SoundFile.cpp"
    "${gamma_SOURCE_DIR}/src/AudioIO.cpp")
  add_library(gamma ${gamma_src})
  target_include_directories(gamma SYSTEM PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include")
endif()

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
  NAME concurrentqueue
  VERSION 1.0.1
  GITHUB_REPOSITORY cameron314/concurrentqueue
  DOWNLOAD_ONLY YES
)

if (concurrentqueue_ADDED) 
  add_library(concurrentqueue INTERFACE)
  target_include_directories(concurrentqueue SYSTEM INTERFACE "${concurrentqueue_SOURCE_DIR}")
endif()

CPMAddPackage(
  NAME yamc
  GITHUB_REPOSITORY yohhoy/yamc
  GIT_TAG fc378ad9c4169a876e769b91c7d2bddf669d1a91
  DOWNLOAD_ONLY YES
)

if (yamc_ADDED)
  add_library(yamc INTERFACE)
  target_include_directories(yamc SYSTEM INTERFACE "${yamc_SOURCE_DIR}/include")
endif()


# BOOST

find_package(
  Boost
  1.74.0
)

add_library(otto_boost INTERFACE)

if(Boost_FOUND)
  target_link_libraries(otto_boost INTERFACE Boost::headers)
else()
  # using unofficial fork as boost's lacking good CMake support
  CPMAddPackage("gh:ClausKlein/boost-cmake@1.79.2")
  target_link_libraries(otto_boost INTERFACE Boost::boost)
endif()

# SKIA

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
    GIT_TAG 832c817bc8a9567aa379181e71e7c602d2480de8
    DOWNLOAD_ONLY YES
  )

  if (skia_ADDED)
    #set(skia_LIB_LOCATION "${skia_BINARY_DIR}/out/Static/libskia.a")
    set(skia_ARGS "\
  is_debug=true \
  paragraph_gms_enabled=false \
  paragraph_tests_enabled=false \
  skia_enable_android_utils=false \
  skia_enable_api_available_macro=true \
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
  skia_enable_particles=false \
  skia_enable_pdf=false \
  skia_enable_skottie=false \
  skia_enable_skparagraph=true \
  skia_enable_skrive=false \
  skia_enable_skshaper=false \
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
  skia_use_zlib=true \
  extra_cflags=[\"-Wno-unknown-warning-option\",\"-Wno-uninitialized\"] \
  extra_cflags_cc=[\"-frtti\",\"-Wno-invalid-offsetof\"] \
  extra_ldflags=[] \
")
    if (OTTO_ENABLE_ASAN)
      # This makes sure rtti is not disabled for skia
      #string(APPEND skia_ARGS " sanitize=\"ASAN\" ")
    endif()

    message("Downloading skia third party dependencies (might take a while)...")
    execute_process(
      COMMAND python tools/git-sync-deps
      WORKING_DIRECTORY "${skia_SOURCE_DIR}"  
    )
    message("Generating skia gn project...")
    # Add this when we can require cmake 3.19
    # COMMAND_ERROR_IS_FATAL ANY
    execute_process(
      COMMAND bin/gn gen "${skia_BINARY_DIR}/out/config" --ide=json --args=${skia_ARGS}
      WORKING_DIRECTORY "${skia_SOURCE_DIR}"  
    )
    message("Generating skia cmake project...")
    execute_process(
      COMMAND python "${skia_SOURCE_DIR}/gn/gn_to_cmake.py" "${skia_BINARY_DIR}/out/config/project.json"
      WORKING_DIRECTORY "${skia_SOURCE_DIR}"  
    )
    set(CMAKE_CXX_STANDARD 17)
    add_subdirectory("${skia_BINARY_DIR}/out/config" "${skia_BINARY_DIR}/build" EXCLUDE_FROM_ALL)
    # Remove the include directories to make sure they are added as system includes
    set_target_properties(skia PROPERTIES INCLUDE_DIRECTORIES "")
    target_include_directories(skia PUBLIC SYSTEM "${skia_SOURCE_DIR}/")
    target_include_directories(skia PUBLIC SYSTEM "${skia_SOURCE_DIR}/include/core")
    target_include_directories(skia PUBLIC SYSTEM "${skia_SOURCE_DIR}/include/effects")
    target_include_directories(skia PUBLIC SYSTEM "${skia_SOURCE_DIR}/include/gpu")
    # Make definitions public
    # TODO: Maybe filter some of these out?
    get_target_property(SKIA_COMP_DEFS skia COMPILE_DEFINITIONS)
    list(REMOVE_ITEM SKIA_COMP_DEFS "SKIA_IMPLEMENTATION=1")
    set_target_properties(skia PROPERTIES INTERFACE_COMPILE_DEFINITIONS "${SKIA_COMP_DEFS}")
  endif()
endif()
