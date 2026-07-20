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

if (APPLE)
  target_compile_definitions(rtaudio PUBLIC "__MACOSX_CORE__")
  target_compile_definitions(rtmidi PUBLIC "__MACOSX_CORE__")
  find_library(COREAUDIO_LIB CoreAudio REQUIRED)
  find_library(COREMIDI_LIB CoreMIDI REQUIRED)
  find_library(COREFOUNDATION_LIB CoreFoundation REQUIRED)
  find_library(AUDIOTOOLBOX_LIB AudioToolbox REQUIRED)
  find_library(AUDIOUNIT_LIB AudioUnit REQUIRED)
  target_link_libraries(rtaudio PUBLIC
    ${COREAUDIO_LIB}
    ${COREFOUNDATION_LIB}
    ${AUDIOTOOLBOX_LIB}
    ${AUDIOUNIT_LIB}
  )
  target_link_libraries(rtmidi PUBLIC
    ${COREMIDI_LIB}
    ${COREFOUNDATION_LIB}
  )
else()
  target_compile_definitions(rtaudio PUBLIC "__LINUX_ALSA__")
  target_compile_definitions(rtmidi PUBLIC "__LINUX_ALSA__")

  # Check for Jack (any OS)
  find_library(JACK_LIB jack)
  find_package(PkgConfig)
  pkg_check_modules(jack jack)
  if(JACK_LIB OR jack_FOUND)
    target_compile_definitions(rtaudio PUBLIC "__UNIX_JACK__")
    target_link_libraries(rtaudio PUBLIC ${jack_LIBRARIES})
    target_compile_definitions(rtmidi PUBLIC "__UNIX_JACK__")
    target_link_libraries(rtmidi PUBLIC ${jack_LIBRARIES})
  endif()

  # Check for Pulse (any OS)
  pkg_check_modules(pulse libpulse-simple)

  if (pulse_FOUND)
    find_library(PULSE_LIB pulse)
    find_library(PULSESIMPLE_LIB pulse-simple)
    target_link_libraries(rtaudio PUBLIC ${PULSE_LIB} ${PULSESIMPLE_LIB})
    target_compile_definitions(rtaudio PUBLIC "__LINUX_PULSE__")
    target_link_libraries(rtmidi PUBLIC ${PULSE_LIB} ${PULSESIMPLE_LIB})
    target_compile_definitions(rtmidi PUBLIC "__LINUX_PULSE__")
  endif()

  target_link_libraries(rtaudio PUBLIC asound)
endif()

target_link_libraries(otto_src PUBLIC rtaudio)
target_link_libraries(otto_src PUBLIC rtmidi)
