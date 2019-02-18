otto_include_board(parts/ui/egl)
otto_include_board(parts/audio/rtaudio)
set(OTTO_USE_FBCP ON)
set(CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE} -ffast-math -funsafe-math-optimizations -mfpu=neon-vfpv4")
