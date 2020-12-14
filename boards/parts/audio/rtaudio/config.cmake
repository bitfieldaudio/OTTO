CPMAddPackage(
  NAME rtaudio
  GITHUB_REPOSITORY thestk/rtaudio
  GIT_TAG 5.1.0
  DOWNLOAD_ONLY YES
)

CPMAddPackage(
  NAME rtmidi
  GITHUB_REPOSITORY thestk/rtmidi
  GIT_TAG 4.0.0
  DOWNLOAD_ONLY YES
)

add_library(rtaudio "${rtaudio_SOURCE_DIR}/RtAudio.cpp")
target_include_directories(rtaudio PUBLIC "${rtaudio_SOURCE_DIR}")

add_library(rtmidi "${rtmidi_SOURCE_DIR}/RtMidi.cpp")
target_include_directories(rtmidi PUBLIC "${rtmidi_SOURCE_DIR}")

target_compile_definitions(rtaudio PUBLIC "-D__LINUX_ALSA__")
target_compile_definitions(rtmidi PUBLIC "-D__LINUX_ALSA__")

# Check for Jack (any OS)
find_library(JACK_LIB jack)
find_package(PkgConfig)
pkg_check_modules(jack jack)
if(JACK_LIB OR jack_FOUND)
  target_compile_definitions(rtaudio PUBLIC "-D__UNIX_JACK__")
  target_link_libraries(rtaudio PUBLIC ${jack_LIBRARIES})
  target_compile_definitions(rtmidi PUBLIC "-D__UNIX_JACK__")
  target_link_libraries(rtmidi PUBLIC ${jack_LIBRARIES})
endif()

# Check for Pulse (any OS)
pkg_check_modules(pulse libpulse-simple)

if (pulse_FOUND)
  find_library(PULSE_LIB pulse)
  find_library(PULSESIMPLE_LIB pulse-simple)
  target_link_libraries(rtaudio PUBLIC ${PULSE_LIB} ${PULSESIMPLE_LIB})
  target_compile_definitions(rtaudio PUBLIC "-D__LINUX_PULSE__")
  target_link_libraries(rtmidi PUBLIC ${PULSE_LIB} ${PULSESIMPLE_LIB})
  target_compile_definitions(rtmidi PUBLIC "-D__LINUX_PULSE__")
endif()

target_link_libraries(rtaudio PUBLIC asound)
target_link_libraries(otto_src PUBLIC rtaudio)
target_link_libraries(otto_src PUBLIC rtmidi)
