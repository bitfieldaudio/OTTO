#include "board/audio_driver.hpp"

#include <chrono>
#include <string>
#include <vector>

#include <fmt/format.h>

#include "util/algorithm.hpp"

#include "core/audio/processor.hpp"

#include "services/audio_manager.hpp"
#include "services/engine_manager.hpp"
#include "services/log_manager.hpp"

#include <Gamma/Domain.h>

namespace otto::services {

  RTAudioAudioManager::RTAudioAudioManager()
  {
    init_audio();
    try {
      init_midi();
    } catch (const RtMidiError& error) {
      LOGE("Midi error: {}", error.getMessage());
      LOGE("Ignoring error and continuing");
    }
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
    RtAudio::StreamParameters outParameters;
    outParameters.deviceId = client.getDefaultOutputDevice();
    outParameters.nChannels = 2;
    outParameters.firstChannel = 0;
    RtAudio::StreamParameters inParameters;
    inParameters.deviceId = client.getDefaultInputDevice();
    inParameters.nChannels = 1;
    inParameters.firstChannel = 0;

    RtAudio::StreamOptions options;
    options.flags = RTAUDIO_SCHEDULE_REALTIME;
    options.numberOfBuffers = 1;
    options.streamName = "OTTO";
    unsigned buf_siz = _buffer_size;

    try {
      client.openStream(&outParameters, enable_input ? &inParameters : nullptr, RTAUDIO_FLOAT32,
                        _samplerate, &buf_siz,
                        [](void* out, void* in, unsigned int nframes, double time,
                           RtAudioStreamStatus status, void* _self) {
                          auto* self = static_cast<RTAudioAudioManager*>(_self);
                          return self->process((float*) out, (float*) in , nframes, time, status);
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
  }

  void RTAudioAudioManager::init_midi()
  {
    midi_out.emplace(RtMidi::Api::UNSPECIFIED, "OTTO");
    midi_in.emplace(RtMidi::Api::UNSPECIFIED, "OTTO");

    for (unsigned i = 0; i < midi_out->getPortCount(); i++) {
      auto port = midi_out->getPortName(i);
      if (!util::starts_with(port, "OTTO:") &&
          !util::starts_with(port, "Midi Through:Midi Through")) {
        midi_out->openPort(i, "out");
        DLOGI("Connected OTTO:out to midi port {}", port);
      }
    }

    for (unsigned i = 0; i < midi_in->getPortCount(); i++) {
      auto port = midi_in->getPortName(i);
      if (!util::starts_with(port, "OTTO:") &&
          !util::starts_with(port, "Midi Through:Midi Through")) {
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
    _buffer_number++;
    auto running = this->running() && Application::current().running();
    if (!running) {
      return 0;
    }

    if ((unsigned) nframes > _buffer_size) {
      LOGE("RTAudio requested more frames than expected");
      return 0;
    }

    clock::time_point t0 = clock::now();

    midi_bufs.swap();

    int ref_count = 0;
    auto in_buf = enable_input ? core::audio::AudioBufferHandle(in_data, nframes, ref_count) : Application::current().audio_manager->buffer_pool().allocate_clear();
    // steal the inner midi buffer
    auto out = Application::current().engine_manager->process(
      {in_buf, {std::move(midi_bufs.inner())}, nframes});

    // process_audio_output(out);

    LOGW_IF(out.nframes != nframes, "Frames went missing!");

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
} // namespace otto::services

// kak: other_file=../include/board/audio_driver.hpp
