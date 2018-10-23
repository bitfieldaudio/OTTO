#include "board/audio_driver.hpp"

#include <string>
#include <vector>

#include <fmt/format.h>

#include "util/algorithm.hpp"
#include "util/timer.hpp"

#include "core/audio/processor.hpp"
#include "core/globals.hpp"

#include "services/audio.hpp"
#include "services/engines.hpp"
#include "services/logger.hpp"

namespace otto::service::audio {

  RTAudioDriver& RTAudioDriver::get() noexcept
  {
    static RTAudioDriver instance{};
    return instance;
  }

  core::audio::AudioBufferPool& RTAudioDriver::buffer_pool()
  {
    return *_buffer_pool;
  }

  void RTAudioDriver::init()
  {
    init_audio();
    try {
      init_midi();
    } catch (const RtMidiError& error) {
      LOGE("Midi error: {}", error.getMessage());
      LOGE("Ignoring error and continuing");
    }
  }

  void RTAudioDriver::init_audio()
  {
    std::vector<RtAudio::Api> apis;
    client.getCompiledApi(apis);

    for (auto& api : apis) {
      DLOGI("RtApi: {}", api);
    }
    RtAudio::StreamParameters outParameters;
    outParameters.deviceId = client.getDefaultOutputDevice();
    outParameters.nChannels = 2;
    outParameters.firstChannel = 0;
    RtAudio::StreamParameters inParameters;
    inParameters.deviceId = client.getDefaultInputDevice();
    inParameters.nChannels = 1;
    inParameters.firstChannel = 0;

    try {
      client.openStream(&outParameters, &inParameters, RTAUDIO_FLOAT32, samplerate, &buffer_size,
                        [](void* out, void* in, unsigned int nframes, double time,
                           RtAudioStreamStatus status, void* self) {
                          return static_cast<RTAudioDriver*>(self)->process(
                            (float*) out, (float*) in, nframes, time, status);
                        },
                        this);
      _buffer_pool = std::make_unique<AudioBufferPool>(buffer_size);
      client.startStream();
    } catch (RtAudioError& e) {
      e.printMessage();
      throw;
    }
  }

  void RTAudioDriver::init_midi()
  {
    midi_in = RtMidiIn();
    midi_out = RtMidiOut();
    midi_out->setClientName("OTTO");
    midi_out->setPortName("otto_out");
    midi_in->setClientName("OTTO");
    midi_in->setPortName("otto_in");

    for (int i = 0; i < midi_out->getPortCount(); i++) {
      auto port = midi_out->getPortName(i);
      if (port != "otto_in") {
        midi_out->openPort(i);
      }
      DLOGI("Connected otto_out to midi port {}", port);
    }

    for (int i = 0; i < midi_in->getPortCount(); i++) {
      auto port = midi_in->getPortName(i);
      if (port != "otto_out") {
        midi_in->openPort(i);
      }
      DLOGI("Connected otto_in to midi port {}", port);
    }

    midi_in->setCallback(
      [](double timeStamp, std::vector<unsigned char>* message, void* userData) {
        auto& self = *static_cast<RTAudioDriver*>(userData);
        self.send_midi_event(core::midi::from_bytes(*message));
      },
      this);
  }

  void RTAudioDriver::shutdown()
  {
    if (client.isStreamOpen()) client.closeStream();
  }

  void RTAudioDriver::send_midi_event(core::midi::AnyMidiEvent evt) noexcept
  {
    midi_bufs.outer().emplace_back(std::move(evt));
  }


  int RTAudioDriver::process(float* out_data,
                             float* in_data,
                             int nframes,
                             double stream_time,
                             RtAudioStreamStatus stream_status)
  {
    auto running = audio::running() && global::running();
    if (!running) {
      return 0;
    }

    TIME_SCOPE("RTAudio::Process");

    if ((unsigned) nframes > buffer_size) {
      LOGE("RTAudio requested more frames than expected");
      return 0;
    }

    midi_bufs.swap();

    int ref_count = 0;
    auto in_buf = AudioBufferHandle(in_data, nframes, ref_count);
    auto out = engines::process({in_buf, {midi_bufs.inner()}, nframes});

    audio::process_audio_output(out);

    LOGW_IF(out.nframes != nframes, "Frames went missing!");

    // Separate channels
    for (int i = 0; i < nframes; i++) {
      out_data[i * 2] = std::get<0>(out.audio[i]);
      out_data[i * 2 + 1] = std::get<1>(out.audio[i]);
    }

    if (midi_out) {
      for (auto& ev : out.midi) {
        util::match(ev, [this](auto& ev) {
          auto bytes = ev.to_bytes();
          midi_out->sendMessage(bytes.data(), bytes.size());
        });
      }
    }
    return 0;
  }
} // namespace otto::service::audio

// kak: other_file=../include/board/audio_driver.hpp
