#pragma once

#include <atomic>
#include <optional>
#include <string>
#include <vector>

#include "core/audio/midi.hpp"
#include "core/audio/processor.hpp"
#include "util/locked.hpp"

#include <RtAudio.h>
#include <RtMidi.h>

#include "services/audio_manager.hpp"

namespace otto::services {

  struct RTAudioAudioManager final : AudioManager {
    RTAudioAudioManager();

    template<typename Parser>
    void add_args(Parser& cli);

    void log_devices();

    static RTAudioAudioManager& current()
    {
      return dynamic_cast<RTAudioAudioManager&>(AudioManager::current());
    }

  protected:
    int process(float* out_buf, float* in_buf, int nframes, double stream_time, RtAudioStreamStatus stream_status);

    void init_audio();
    void init_midi();

    RtAudio client;
    // optional is used to delay construction to the init phaase, where errros can be handled
    std::optional<RtMidiIn> midi_in = std::nullopt;
    std::optional<RtMidiOut> midi_out = std::nullopt;
    bool enable_input = true;

    int device_in_ = client.getDefaultInputDevice();
    int device_out_ = client.getDefaultOutputDevice();
  };

#ifdef LYRA_OPT_HPP
  template<typename Parser>
  void RTAudioAudioManager::add_args(Parser& cli)
  {
    cli |= lyra::opt(device_in_, "input device")["--audio-in"]("The input device number");
    cli |= lyra::opt(device_out_, "output device")["--audio-out"]("The output device number");
  }
#endif

} // namespace otto::services

// kak: other_file=../../src/audio_driver.cpp
