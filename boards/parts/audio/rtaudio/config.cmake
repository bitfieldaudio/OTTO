if(APPLE) 
    target_compile_definitions(otto PUBLIC "__MACOSX_CORE__")
    target_link_libraries(otto PUBLIC 
        "-framework CoreAudio"
        "-framework CoreMIDI"
        "-framework AudioToolbox")
else()
    target_compile_definitions(otto PUBLIC "__LINUX_ALSA__")
    target_link_libraries(otto PUBLIC asound)
endif()
