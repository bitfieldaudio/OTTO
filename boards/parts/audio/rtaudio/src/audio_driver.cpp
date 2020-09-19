#include "app/services/config.hpp"
#include "app/services/impl/audio.hpp"

#include <Gamma/Domain.h>

#include <RtAudio.h>

namespace otto::services {

  struct RtAudioConfig : Config<RtAudioConfig> {
    static constexpr util::string_ref name = "RtAudio";
    std::string input_device = "";
    std::string output_device = "";
    unsigned buffer_size = 256;
    unsigned sample_rate = 44100;

    DECL_VISIT(input_device, output_device)
  };

  struct RtAudioService final : AudioImpl {
    RtAudioService()
    {
      i_params.nChannels = 2;
      i_params.deviceId = adac.getDefaultInputDevice();
      o_params.nChannels = 2;
      o_params.deviceId = adac.getDefaultOutputDevice();
      for (int i = 0; i < adac.getDeviceCount(); i++) {
        const auto& device = adac.getDeviceInfo(i);
        if (device.name == conf->input_device) {
          i_params.deviceId = i;
        }
        if (device.name == conf->output_device) {
          o_params.deviceId = i;
        }
      }
      LOGI("Available audio devices:");
      for (int i = 0; i < adac.getDeviceCount(); i++) {
        const auto& device = adac.getDeviceInfo(i);
        LOGI(" - '{}'. {} input channels, {} output channels, {} duplex channels", device.name, device.inputChannels,
             device.outputChannels, device.duplexChannels);
      }
      LOGI("Select one by setting 'RtAudio.(input|output)_device' to the name in config");
      auto idev = adac.getDeviceInfo(i_params.deviceId);
      auto odev = adac.getDeviceInfo(o_params.deviceId);
      LOGI("Current input device: '{}'", idev.name);
      LOGI("Current output device: '{}'", odev.name);
      if (idev.inputChannels == 1) LOGW("Input device is mono");
      if (idev.inputChannels == 0) LOGW("Invalid or no input device selected. Continuing without audio input");
      i_params.nChannels = idev.inputChannels;

      init_audio();
    }

    void init_audio()
    {
      RtAudio::StreamOptions opts;
      opts.flags = RTAUDIO_SCHEDULE_REALTIME;
      opts.numberOfBuffers = 1;
      opts.streamName = "OTTO";
      unsigned buffer_size = conf->buffer_size;
      unsigned samplerate = conf->sample_rate;
      adac.openStream(
        &o_params, &i_params, RTAUDIO_FLOAT32, samplerate, &buffer_size,
        [](void* out, void* in, unsigned nframes, double time, RtAudioStreamStatus status, void* self_) {
          return static_cast<RtAudioService*>(self_)->rtaudio_cb((float*) out, (float*) in, nframes, time, status);
        },
        this, &opts);
      LOGI("Buffer size: {}", buffer_size);
      set_buffer_size(buffer_size);
      gam::sampleRate(samplerate);

      adac.startStream();
    }

  private:
    int rtaudio_cb(float* out, float* in, int nframes, double time, RtAudioStreamStatus status) noexcept
    {
      if (status) LOGE("Audio Over/undrerun!");
      auto input_buf = buffer_pool().allocate_stereo();
      auto output_buf = buffer_pool().allocate_stereo().clear();
      CallbackData cbd = {
        .input = input_buf,
        .output = output_buf,
      };
      // Deinterleave and copy input audio
      if (i_params.nChannels == 2) {
        for (int i = 0; i < nframes; i++) {
          input_buf.left[i] = in[i * 2];
          input_buf.right[i] = in[i * 2 + 1];
        }
      } else if (i_params.nChannels == 1) {
        std::copy_n(in, nframes, input_buf.left.begin());
        std::copy_n(in, nframes, input_buf.right.begin());
      } else if (i_params.nChannels == 0) {
        input_buf.clear();
      }
      if (callback_) callback_(cbd);
      executor_.run_queued_functions();
      // Interleave audio
      for (int i = 0; i < nframes; i++) {
        out[i * 2] = cbd.output.left[i];
        out[i * 2 + 1] = cbd.output.right[i];
      }
      return 0;
    }

    std::vector<RtAudio::Api> get_apis()
    {
      std::vector<RtAudio::Api> res;
      adac.getCompiledApi(res);
      return res;
    }

    ConfHandle<RtAudioConfig> conf;
    RtAudio adac;
    RtAudio::StreamParameters i_params;
    RtAudio::StreamParameters o_params;
  };

  core::ServiceHandle<Audio> Audio::make_board()
  {
    return core::make_handle<RtAudioService>();
  }
} // namespace otto::services
