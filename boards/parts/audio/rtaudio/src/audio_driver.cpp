#include "board/audio_driver.hpp"

#include <Gamma/Domain.h>
#include <fmt/format.h>

#include <chrono>
#include <string>
#include <vector>

#include "core/audio/processor.hpp"
#include "services/audio_manager.hpp"
#include "services/clock_manager.hpp"
#include "services/engine_manager.hpp"
#include "services/log_manager.hpp"
#include "util/algorithm.hpp"

namespace otto::services {

#ifndef __LINUX_ALSA__
  AlsaMixer::AlsaMixer() = default;
  AlsaMixer::~AlsaMixer() = default;

  void AlsaMixer::set_volume(float both) {}
  void AlsaMixer::set_volume_l(float l) {}
  void AlsaMixer::set_volume_r(float r) {}

  AlsaMixer::AlsaMixer(util::string_ref card, int subdevice_idx, util::string_ref elem_name, bool is_capture) {}
#else
  AlsaMixer::AlsaMixer() = default;
  AlsaMixer::AlsaMixer(util::string_ref card, int subdevice_idx, util::string_ref elem_name, bool is_capture)
    : is_capture(is_capture)
  {
    ::snd_mixer_open(&snd_mixer_, 0);
    ::snd_mixer_attach(snd_mixer_, "default");
    ::snd_mixer_selem_register(snd_mixer_, nullptr, nullptr);
    ::snd_mixer_load(snd_mixer_);

    ::snd_mixer_selem_id_t* sid;
    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, subdevice_idx);
    snd_mixer_selem_id_set_name(sid, elem_name.c_str());
    snd_mixer_elem_ = ::snd_mixer_find_selem(snd_mixer_, sid);
    if (snd_mixer_elem_ == nullptr) {
      LOGE("snd_mixer_elem_ was not found!");
      return;
    }

    if (is_capture) {
      snd_mixer_selem_get_capture_volume_range(snd_mixer_elem_, &min_vol, &max_vol);
    } else {
      snd_mixer_selem_get_playback_volume_range(snd_mixer_elem_, &min_vol, &max_vol);
    }
  }
  AlsaMixer::~AlsaMixer()
  {
    if (snd_mixer_elem_) ::snd_mixer_close(snd_mixer_);
  }

  void AlsaMixer::set_volume(float both)
  {
    if (!snd_mixer_) return;
    if (!snd_mixer_elem_) return;
    if (is_capture) {
      // TODO: These lines fail on my machine - figure what is going wrong --Jonatan
      snd_mixer_selem_set_capture_volume_all(snd_mixer_elem_, (max_vol - min_vol) * both + min_vol);
    } else {
      snd_mixer_selem_set_playback_volume_all(snd_mixer_elem_, (max_vol - min_vol) * both + min_vol);
    }
  }
  void AlsaMixer::set_volume_l(float l)
  {
    if (!snd_mixer_) return;
    if (!snd_mixer_elem_) return;
    if (is_capture) {
      snd_mixer_selem_set_capture_volume(snd_mixer_elem_, SND_MIXER_SCHN_FRONT_LEFT, (max_vol - min_vol) * l + min_vol);
    } else {
      snd_mixer_selem_set_playback_volume(snd_mixer_elem_, SND_MIXER_SCHN_FRONT_LEFT,
                                          (max_vol - min_vol) * l + min_vol);
    }
  }

  void AlsaMixer::set_volume_r(float r)
  {
    if (!snd_mixer_) return;
    if (!snd_mixer_elem_) return;
    if (is_capture) {
      snd_mixer_selem_set_capture_volume(snd_mixer_elem_, SND_MIXER_SCHN_FRONT_RIGHT,
                                         (max_vol - min_vol) * r + min_vol);
    } else {
      snd_mixer_selem_set_playback_volume(snd_mixer_elem_, SND_MIXER_SCHN_FRONT_RIGHT,
                                          (max_vol - min_vol) * r + min_vol);
    }
  }

#endif

  AlsaMixer AlsaMixer::playback(RtAudio& client, int device_idx)
  {
    return AlsaMixer("default", 0, "Master", false);
  }
  AlsaMixer AlsaMixer::capture(RtAudio& client, int device_idx)
  {
    return AlsaMixer("default", 0, "Mic", true);
  }


  RTAudioAudioManager::RTAudioAudioManager(int in_device, int out_device)
    : device_in_(in_device), device_out_(out_device)
  {
    init_audio();
    try {
      init_midi();
    } catch (const RtMidiError& error) {
      LOGE("Midi error: {}", error.getMessage());
      LOGE("Ignoring error and continuing");
    }
  }

  void RTAudioAudioManager::log_devices()
  {
    LOGI("Avaliable RtAudio devices:");
    for (auto i = 0; i < client.getDeviceCount(); i++) {
      auto info = client.getDeviceInfo(i);
      LOGI("{}: '{}'. {} in channels, {} out channels, {} duplex channels", i, info.name, info.inputChannels,
           info.outputChannels, info.duplexChannels);
    }
    LOGI("Currently in={} and out={} will be used, but this can be changed with --audio-in=n and --audio-out=n",
         device_in_, device_out_);
  }

  void RTAudioAudioManager::init_audio()
  {
#ifndef NDEBUG
    std::vector<RtAudio::Api> apis;
    client.getCompiledApi(apis);

    for (auto& api : apis) {
      DLOGI("RtApi: {}", api);
    }
#endif

    if (device_in_ < 0 or device_in_ >= client.getDeviceCount()) device_in_ = client.getDefaultInputDevice();
    if (device_out_ < 0 or device_out_ >= client.getDeviceCount()) device_out_ = client.getDefaultOutputDevice();

    RtAudio::StreamParameters outParameters;
    outParameters.deviceId = device_out_;
    outParameters.nChannels = 2;
    outParameters.firstChannel = 0;
    RtAudio::StreamParameters inParameters;
    inParameters.deviceId = device_in_;
    inParameters.nChannels = 2;
    inParameters.firstChannel = 0;

    RtAudio::StreamOptions options;
    options.flags = RTAUDIO_SCHEDULE_REALTIME;
    options.numberOfBuffers = 1;
    options.streamName = "OTTO";
    unsigned buf_siz = _buffer_size;

    try {
      client.openStream(
        &outParameters, enable_input ? &inParameters : nullptr, RTAUDIO_FLOAT32, _samplerate, &buf_siz,
        [](void* out, void* in, unsigned int nframes, double time, RtAudioStreamStatus status, void* _self) {
          auto* self = static_cast<RTAudioAudioManager*>(_self);
          return self->process((float*) out, (float*) in, nframes, time, status);
        },
        this, &options);
      _buffer_size = buf_siz;
      buffer_pool().set_buffer_size(buf_siz);
      client.startStream();
      gam::sampleRate(samplerate());
    } catch (RtAudioError& e) {
      e.printMessage();
      if (enable_input) {
        // try again without an input
        enable_input = false;
        init_audio();
      } else {
        throw;
      }
    }
    output_volume = AlsaMixer::playback(client, device_out_);
    line_in_gain = AlsaMixer::capture(client, device_in_);
  }

  void RTAudioAudioManager::init_midi()
  {
    midi_out.emplace(RtMidi::Api::UNSPECIFIED, "OTTO");
    midi_in.emplace(RtMidi::Api::UNSPECIFIED, "OTTO");

    for (unsigned i = 0; i < midi_out->getPortCount(); i++) {
      auto port = midi_out->getPortName(i);
      if (!util::starts_with(port, "OTTO:") && !util::starts_with(port, "Midi Through:Midi Through")) {
        midi_out->openPort(i, "out");
        DLOGI("Connected OTTO:out to midi port {}", port);
      }
    }

    for (unsigned i = 0; i < midi_in->getPortCount(); i++) {
      auto port = midi_in->getPortName(i);
      if (!util::starts_with(port, "OTTO:") && !util::starts_with(port, "Midi Through:Midi Through")) {
        midi_in->openPort(i, "in");
        DLOGI("Connected OTTO:in to midi port {}", port);
      }
    }

    midi_in->setCallback(
      [](double timeStamp, std::vector<unsigned char>* message, void* userData) {
        auto& self = *static_cast<RTAudioAudioManager*>(userData);
        try {
          self.send_midi_event(core::midi::from_bytes(*message));
        } catch (util::exception& e) {
          LOGE("Error parsing midi: {}", e.what());
        }
      },
      this);
  }

  using clock = std::chrono::high_resolution_clock;

  int RTAudioAudioManager::process(float* out_data,
                                   float* in_data,
                                   int nframes,
                                   double stream_time,
                                   RtAudioStreamStatus stream_status)
  {
    pre_process_tasks();
    auto running = this->running() && Application::current().running();
    if (!running) {
      return 0;
    }

    if ((unsigned) nframes != _buffer_size) {
      LOGE("RTAudio requested {} frames. expected {}", nframes, _buffer_size);
      return 0;
    }

    if (stream_status != 0) {
      LOGE("RTAudioStreamStatus == {:x}", stream_status);
    }

    clock::time_point t0 = clock::now();

    midi_bufs.swap();

    auto in_buf = Application::current().audio_manager->buffer_pool().allocate_multi<2>();
    if (enable_input) {
      // Deinterleave
      for (int i = 0; i < nframes; i++) {
        in_buf[0][i] = in_data[2 * i];
        in_buf[1][i] = in_data[2 * i + 1];
      }
    } else {
      // Is this necessary? We could also just not even add it to the output.
      nano::fill(in_buf[0], 0.f);
      nano::fill(in_buf[1], 0.f);
    }

    // steal the inner midi buffer
    auto out = Application::current().engine_manager->process(
      {in_buf, {std::move(midi_bufs.inner())}, core::clock::ClockRange{}});

    core::audio::validate_audio(out.audio[0]);
    core::audio::validate_audio(out.audio[1]);

    // process_audio_output(out);

    LOGE_IF(out.nframes != nframes, "Frames went missing!");

    // Separate channels
    for (int i = 0; i < nframes; i++) {
      out_data[i * 2] = out.audio[0][i];
      out_data[i * 2 + 1] = out.audio[1][i];
    }

    if (midi_out) {
      for (auto& ev : out.midi) {
        util::match(ev, [this](auto& ev) {
          auto bytes = ev.to_bytes();
          midi_out->sendMessage(bytes.data(), bytes.size());
        });
      }
    }

    // return the midi buffer
    midi_bufs.inner() = out.midi.move_vector_out();

    clock::time_point t1 = clock::now();

    _cpu_time.add(std::chrono::nanoseconds(t1 - t0).count() / (1e9 / float(_samplerate) * nframes));

    return 0;
  }

#ifndef __LINUX_ALSA__
  void RTAudioAudioManager::line_in_gain_l(float gain) {}
  void RTAudioAudioManager::line_in_gain_r(float) {}
  void RTAudioAudioManager::output_vol(float) {}
#else

  void RTAudioAudioManager::line_in_gain_l(float gain)
  {
    line_in_gain.set_volume_l(gain);
  }
  void RTAudioAudioManager::line_in_gain_r(float gain)
  {
    line_in_gain.set_volume_r(gain);
  }
  void RTAudioAudioManager::output_vol(float vol)
  {
    output_volume.set_volume(vol);
  }
#endif

} // namespace otto::services

// kak: other_file=../include/board/audio_driver.hpp
