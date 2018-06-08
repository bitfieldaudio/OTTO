#pragma once

// This file is processed by cmake and included automatically in all C/C++ files.
// Make sure to edit config.hpp and not config.example.hpp. The example file is
// copied automatically if config.hpp does not exist. Do not include config.hpp
// in a commit.

// #cmakedefine VAR will define the variable VAR if it is ON in cmake.
// #cmakedefine01 VAR defines VAR to 1 if VAR is ON in cmake.
// @VAR@ or ${VAR} will expand to the value of the cmake variable VAR

// Compile for the raspberry pi
#cmakedefine01 OTTO_RPI

// Compile and run the IMGUI debug ui.
#cmakedefine01 OTTO_DEBUG_UI

// Compile and run timers
#cmakedefine01 OTTO_ENABLE_TIMERS


// Run the UI in raspberry pi specific EGL
#define OTTO_UI_EGL OTTO_RPI

// Run the ui in GLFW
#define OTTO_UI_GLFW !OTTO_RPI

// Use alsa directly for audio
#define OTTO_AUDIO_ALSA OTTO_RPI

// Use jack for audio
#define OTTO_AUDIO_JACK !OTTO_RPI
