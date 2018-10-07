target_link_libraries(otto PUBLIC asound)
target_compile_definitions(otto PUBLIC "__LINUX_ALSA__")
