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

namespace otto::service::audio {
  struct RTAudioDriver {
    static RTAudioDriver& get() noexcept;

    void init();
    void shutdown();

    std::atomic_int samplerate = 48000;

    void send_midi_event(core::midi::AnyMidiEvent) noexcept;

    core::audio::AudioBufferPool& buffer_pool();

  private:
    RTAudioDriver() = default;
    ~RTAudioDriver() noexcept = default;

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

    unsigned buffer_size = 256;

    util::atomic_swap<core::midi::shared_vector<core::midi::AnyMidiEvent>> midi_bufs = {{}, {}};

    std::unique_ptr<core::audio::AudioBufferPool> _buffer_pool;
  };

  using AudioDriver = RTAudioDriver;
} // namespace otto::service::audio

// kak: other_file=../../src/audio_driver.cpp
