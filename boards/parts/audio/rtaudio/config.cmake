CPMAddPackage(
  NAME rtaudio
  GITHUB_REPOSITORY thestk/rtaudio
  GIT_TAG 5.1.0
  OPTIONS
    "BUILD_SHARED_LIBS Off"
    "RTAUDIO_TARGETNAME_UNINSTALL rtaudio-uninstall"
    "BUILD_TESTING Off"
)
target_link_libraries(otto_src PUBLIC rtaudio)

CPMAddPackage(
  NAME rtmidi
  GITHUB_REPOSITORY thestk/rtmidi
  GIT_TAG 4.0.0
  OPTIONS
    "BUILD_SHARED_LIBS Off"
    "RTMIDI_TARGETNAME_UNINSTALL rtmidi-uninstall"
    "BUILD_TESTING Off"
)
target_link_libraries(otto_src PUBLIC rtmidi)
