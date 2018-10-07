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

    //gatherMidiInput(nframes);
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
    return 0;
  }
} // namespace otto::service::audio

// kak: other_file=../include/board/audio_driver.hpp
