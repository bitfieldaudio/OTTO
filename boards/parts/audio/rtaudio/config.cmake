if(APPLE) 
    target_compile_definitions(otto_src PUBLIC "__MACOSX_CORE__")
    target_link_libraries(otto_src PUBLIC 
        "-framework CoreAudio"
        "-framework CoreMIDI"
        "-framework AudioToolbox")
else()
    target_compile_definitions(otto_src PUBLIC "__LINUX_ALSA__")
    target_link_libraries(otto_src PUBLIC asound)

    # Enable jack: - both alsa and jack can be enabled at the same time
    # target_compile_definitions(otto_src PUBLIC "__UNIX_JACK__")
    # target_link_libraries(otto_src PUBLIC jack)
endif()
