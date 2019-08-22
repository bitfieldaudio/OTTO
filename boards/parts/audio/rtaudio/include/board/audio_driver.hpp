#pragma once

#include <atomic>
#include <string>
#include <vector>
#include <optional>

#include "core/audio/midi.hpp"
#include "core/audio/processor.hpp"
#include "util/locked.hpp"

#include <RtAudio.h>
#include <RtMidi.h>

#include "services/audio_manager.hpp"

namespace otto::services {

  struct RTAudioAudioManager final : AudioManager {

    RTAudioAudioManager();

  protected:
    int process(float* out_buf,
                 float* in_buf,
                 int nframes,
                 double stream_time,
                 RtAudioStreamStatus stream_status);

    void init_audio();
    void init_midi();

    RtAudio client;
    // optional is used to delay construction to the init phaase, where errros can be handled
    std::optional<RtMidiIn> midi_in = std::nullopt;
    std::optional<RtMidiOut> midi_out = std::nullopt;
    bool enable_input = true;
  };

} // namespace otto::service::audio

// kak: other_file=../../src/audio_driver.cpp
