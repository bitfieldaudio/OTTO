#pragma once

#include <atomic>
#include <string>
#include <vector>
#include <thread>

#define ALSA_PCM_NEW_HW_PARAMS_API
#include <alsa/asoundlib.h>

#include "core/audio/midi.hpp"
#include "core/audio/processor.hpp"

#include "util/locked.hpp"

namespace otto::service::audio {
  struct AlsaAudioDriver {
    static AlsaAudioDriver& get() noexcept;

    void init();
    void shutdown();

    std::atomic_int samplerate = 44100;

    void send_midi_event(core::midi::AnyMidiEvent);

  private:
    AlsaAudioDriver() = default;
    ~AlsaAudioDriver() noexcept = default;

    void main_loop();
    int process_callback(int nframes);

    snd_pcm_t* playback_handle;
    snd_pcm_t* capture_handle;
    snd_seq_t* seq_handle;

    core::audio::ProcessBuffer<1> in_data;
    util::atomic_swap<std::vector<core::midi::AnyMidiEvent>> midi_bufs;

    std::thread audio_thread;
  };

  using AudioDriver = AlsaAudioDriver;
} // otto::audio
