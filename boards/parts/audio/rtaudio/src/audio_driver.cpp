#include "app/services/audio.hpp"

#include <algorithm>
#include <RtAudio.h>

#include "lib/util/dynamic.hpp"

#include "app/services/config.hpp"

namespace otto::drivers {

  struct RtAudioConfig : Config<RtAudioConfig> {
    static constexpr util::string_ref name = "AudioDriver";
    std::string input_device;
    std::string output_device;
    unsigned buffer_size = 256;
    // 41000 is not a valid CoreAudio rate and crashes device open on macOS.
    unsigned sample_rate = 48000;

    DECL_VISIT(input_device, output_device, buffer_size, sample_rate)
  };

  struct RtAudioDriver final : IAudioDriver {
    RtAudioDriver(const RtAudioConfig& conf);

    void start() override;
    void stop() override;
    void init_audio();

    void set_callback(Callback&& cb) override;
    [[nodiscard]] std::size_t buffer_size() const noexcept override;
    [[nodiscard]] std::size_t sample_rate() const noexcept override;

    IAudioMixer& mixer() noexcept override
    {
      return *mixer_;
    }

  private:
    int rtaudio_cb(float* out, float* in, int nframes, double time, RtAudioStreamStatus status) noexcept;

    std::vector<RtAudio::Api> get_apis();

    Callback callback = nullptr;
    RtAudioConfig conf;
    unsigned buffer_size_ = conf.buffer_size;
    unsigned sample_rate_ = conf.sample_rate;
    RtAudio adac;
    std::vector<float> buffers;
    RtAudio::StreamParameters i_params;
    RtAudio::StreamParameters o_params;
    std::unique_ptr<IAudioMixer> mixer_;
    float software_volume_ = 1.f;
    friend struct RtAudioSoftwareMixer;
  };

  std::unique_ptr<IAudioDriver> IAudioDriver::make_default(services::ConfigManager& confman)
  {
    return std::make_unique<RtAudioDriver>(confman.make_conf<RtAudioConfig>());
  }

  struct RtAudioSoftwareMixer final : IAudioMixer {
    RtAudioSoftwareMixer(RtAudioDriver& d) : driver_(d) {}

    void set_volume(float v) override
    {
      driver_.software_volume_ = v;
    }
    [[nodiscard]] float get_volume() const override
    {
      return driver_.software_volume_;
    }

  private:
    RtAudioDriver& driver_;
  };

  std::unique_ptr<IAudioMixer> IAudioMixer::make_software(IAudioDriver& driver)
  {
    return std::make_unique<RtAudioSoftwareMixer>(dynamic_cast<RtAudioDriver&>(driver));
  }

  RtAudioDriver::RtAudioDriver(const RtAudioConfig& conf) : conf(conf)
  {
    i_params.nChannels = 2;
    i_params.deviceId = adac.getDefaultInputDevice();
    o_params.nChannels = 2;
    o_params.deviceId = adac.getDefaultOutputDevice();
    bool found_input = conf.input_device.empty();
    bool found_output = conf.output_device.empty();

    // When nothing is configured, prefer a healthy duplex device (BlackHole /
    // interfaces) over separate mic/speakers. Skip flaky virtual devices that
    // advertise duplex but can hang CoreAudio on start (Background Music, etc.).
    if (conf.input_device.empty() && conf.output_device.empty()) {
      int best_score = 0;
      int best_index = -1;
      for (int i = 0; i < adac.getDeviceCount(); i++) {
        const auto& device = adac.getDeviceInfo(i);
        if (device.duplexChannels < 2 || device.outputChannels < 2 || device.inputChannels < 2) continue;
        const auto& n = device.name;
        int score = 50;
        if (n.find("BlackHole") != std::string::npos) score = 100;
        else if (n.find("Background Music") != std::string::npos) continue;
        else if (n.find("Zoom") != std::string::npos) continue;
        else if (n.find("Teams") != std::string::npos) continue;
        else if (n.find("UI Sounds") != std::string::npos) continue;
        if (score > best_score) {
          best_score = score;
          best_index = i;
        }
      }
      if (best_index >= 0) {
        i_params.deviceId = best_index;
        o_params.deviceId = best_index;
        LOGI("Auto-selected duplex device '{}'", adac.getDeviceInfo(best_index).name);
      }
    }

    for (int i = 0; i < adac.getDeviceCount(); i++) {
      const auto& device = adac.getDeviceInfo(i);
      if (!conf.input_device.empty() && device.name == conf.input_device) {
        i_params.deviceId = i;
        found_input = true;
      }
      if (!conf.output_device.empty() && device.name == conf.output_device) {
        o_params.deviceId = i;
        found_output = true;
      }
    }
    if (!found_input) LOGW("Configured input device '{}' not found; using default", conf.input_device);
    if (!found_output) LOGW("Configured output device '{}' not found; using default", conf.output_device);

    LOGI("Available audio devices:");
    for (int i = 0; i < adac.getDeviceCount(); i++) {
      const auto& device = adac.getDeviceInfo(i);
      LOGI(" - '{}'. {} input channels, {} output channels, {} duplex channels", device.name, device.inputChannels,
           device.outputChannels, device.duplexChannels);
    }
    LOGI("Select one by setting 'AudioDriver.(input|output)_device' in config");
    auto idev = adac.getDeviceInfo(i_params.deviceId);
    auto odev = adac.getDeviceInfo(o_params.deviceId);
    LOGI("Current input device: '{}'", idev.name);
    LOGI("Current output device: '{}'", odev.name);

    o_params.nChannels = std::min<unsigned>(2, odev.outputChannels);
    i_params.nChannels = std::min<unsigned>(2, idev.inputChannels);
    if (i_params.nChannels == 1) LOGD("Input device is mono");
    if (i_params.nChannels == 0) LOGD("No audio input; output-only");

    // CoreAudio exposes mic and speakers as separate non-duplex devices.
    if (i_params.deviceId != o_params.deviceId && idev.duplexChannels == 0 && odev.duplexChannels == 0 &&
        i_params.nChannels > 0) {
      LOGD("Input and output are separate devices without duplex; using output-only");
      i_params.nChannels = 0;
    }

    try {
      init_audio();
    } catch (const RtAudioError& e) {
      LOGE("Audio device open failed: {}", e.getMessage());
      throw;
    }
    try {
      mixer_ = IAudioMixer::make_default(*this);
    } catch (std::exception& e) {
      LOGW("Error constructing default audio mixer: {}", e.what());
      LOGW("Continuing with software mixer");
      mixer_ = IAudioMixer::make_software(*this);
    }
  }

  void RtAudioDriver::start()
  {
    try {
      if (adac.isStreamOpen() && !adac.isStreamRunning()) adac.startStream();
    } catch (const RtAudioError& e) {
      LOGE("Failed to start audio stream: {}", e.getMessage());
    }
  }

  void RtAudioDriver::stop()
  {
    try {
      if (adac.isStreamRunning()) adac.stopStream();
      if (adac.isStreamOpen()) adac.closeStream();
    } catch (const RtAudioError& e) {
      LOGW("Error stopping audio stream: {}", e.getMessage());
    }
  }

  void RtAudioDriver::init_audio()
  {
    RtAudio::StreamOptions opts;
    opts.flags = RTAUDIO_SCHEDULE_REALTIME;
    opts.numberOfBuffers = 1;
    opts.streamName = "OTTO";
    unsigned samplerate = conf.sample_rate;
    auto callback = [](void* out, void* in, unsigned nframes, double time, RtAudioStreamStatus status, void* self_) {
      return static_cast<RtAudioDriver*>(self_)->rtaudio_cb(static_cast<float*>(out), static_cast<float*>(in),
                                                            static_cast<int>(nframes), time, status);
    };

    auto try_open = [&](bool with_input) {
      RtAudio::StreamParameters* in_params = (with_input && i_params.nChannels > 0) ? &i_params : nullptr;
      adac.openStream(&o_params, in_params, RTAUDIO_FLOAT32, samplerate, &buffer_size_, callback, this, &opts);
    };

    try {
      try_open(true);
    } catch (const RtAudioError& e) {
      if (i_params.nChannels == 0) throw;
      LOGW("Failed to open duplex audio stream ({}). Retrying output-only.", e.getMessage());
      i_params.nChannels = 0;
      try_open(false);
    }
    sample_rate_ = samplerate;
    buffers.resize(buffer_size_ * 4);
    LOGI("Buffer size: {}, sample rate: {}", buffer_size_, sample_rate_);
  }

  int RtAudioDriver::rtaudio_cb(float* out, float* in, int nframes, double time, RtAudioStreamStatus status) noexcept
  {
    if (status != 0) LOGW("Audio Over/undrerun!");
    auto input_buf = util::stereo_audio_buffer(
      util::audio_buffer(std::span(buffers.data() + 0 * buffer_size_, buffer_size_), nullptr),
      util::audio_buffer(std::span(buffers.data() + 1 * buffer_size_, buffer_size_), nullptr));
    auto output_buf = util::stereo_audio_buffer(
      util::audio_buffer(std::span(buffers.data() + 2 * buffer_size_, buffer_size_), nullptr),
      util::audio_buffer(std::span(buffers.data() + 3 * buffer_size_, buffer_size_), nullptr));
    CallbackData cbd = {
      .input = input_buf,
      .output = output_buf,
    };
    // Deinterleave and copy input audio
    if (in != nullptr && i_params.nChannels == 2) {
      for (int i = 0; i < nframes; i++) {
        input_buf.left[i] = in[i * 2];
        input_buf.right[i] = in[i * 2 + 1];
      }
    } else if (in != nullptr && i_params.nChannels == 1) {
      std::copy_n(in, nframes, input_buf.left.begin());
      std::copy_n(in, nframes, input_buf.right.begin());
    } else {
      input_buf.clear();
    }
    if (callback != nullptr) {
      callback(cbd);
    } else {
      cbd.output.clear();
    }
    // Interleave audio
    for (int i = 0; i < nframes; i++) {
      out[i * 2] = cbd.output.left[i] * software_volume_;
      out[i * 2 + 1] = cbd.output.right[i] * software_volume_;
    }
    return 0;
  }


  void RtAudioDriver::set_callback(Callback&& cb)
  {
    callback = std::move(cb);
  }

  std::size_t RtAudioDriver::buffer_size() const noexcept
  {
    return buffer_size_;
  }

  std::size_t RtAudioDriver::sample_rate() const noexcept
  {
    return sample_rate_;
  }

  std::vector<RtAudio::Api> RtAudioDriver::get_apis()
  {
    std::vector<RtAudio::Api> res;
    adac.getCompiledApi(res);
    return res;
  }

} // namespace otto::drivers
