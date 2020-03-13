#pragma once

#include <RtAudio.h>
#include <RtMidi.h>

#include <atomic>
#include <optional>
#include <string>
#include <vector>

#include "core/audio/midi.hpp"
#include "core/audio/processor.hpp"
#include "util/locked.hpp"

#ifdef __LINUX_ALSA__
#include <alsa/asoundlib.h>
#include <alsa/mixer.h>
#endif

#include "services/audio_manager.hpp"

namespace otto::services {

  struct AlsaMixer {
    AlsaMixer();
    ~AlsaMixer();

    void set_volume(float both);
    void set_volume_l(float l);
    void set_volume_r(float r);

    static AlsaMixer playback(RtAudio& client, int device_idx);
    static AlsaMixer capture(RtAudio& client, int device_idx);

  private:
    AlsaMixer(util::string_ref card, int subdevice_idx, util::string_ref elem_name, bool is_capture);
#ifdef __LINUX_ALSA__
    ::snd_mixer_t* snd_mixer_ = nullptr;
    ::snd_mixer_elem_t* snd_mixer_elem_ = nullptr;
    long min_vol = 0;
    long max_vol = 0;
    bool is_capture = false;
#endif
  };

  struct RTAudioAudioManager final : AudioManager {
    RTAudioAudioManager(int in_device = -1, int out_device = -1);

    template<typename Parser>
    void add_args(Parser& cli);

    void log_devices();

    static RTAudioAudioManager& current()
    {
      return dynamic_cast<RTAudioAudioManager&>(AudioManager::current());
    }

    void line_in_gain_l(float) override;
    void line_in_gain_r(float) override;
    void output_vol(float) override;

  protected:
    int process(float* out_buf, float* in_buf, int nframes, double stream_time, RtAudioStreamStatus stream_status);

    void init_audio();
    void init_midi();

    RtAudio client;
    // optional is used to delay construction to the init phaase, where errros can be handled
    std::optional<RtMidiIn> midi_in = std::nullopt;
    std::optional<RtMidiOut> midi_out = std::nullopt;
    bool enable_input = true;

    int device_in_ = -1;
    int device_out_ = -1;

    AlsaMixer output_volume;
    AlsaMixer line_in_gain;
  };
} // namespace otto::services

// kak: other_file=../../src/audio_driver.cpp
