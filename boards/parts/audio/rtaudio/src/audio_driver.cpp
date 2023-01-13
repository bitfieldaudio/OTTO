#include "app/services/audio.hpp"

#include <RtAudio.h>

#include "lib/util/dynamic.hpp"

#include "app/services/config.hpp"

namespace otto::drivers {

  struct RtAudioConfig : Config<RtAudioConfig> {
    static constexpr util::string_ref name = "AudioDriver";
    std::string input_device;
    std::string output_device;
    unsigned buffer_size = 256;
    unsigned sample_rate = 41000;

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
    bool found_output = false;
    for (int i = 0; i < adac.getDeviceCount(); i++) {
      const auto& device = adac.getDeviceInfo(i);
      if (device.name == conf.input_device) {
        i_params.deviceId = i;
      }
      if (device.name == conf.output_device) {
        o_params.deviceId = i;
        found_output = true;
      }
      if (!found_output && o_params.deviceId == 0 && device.outputChannels == 2) {
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
    adac.startStream();
  }

  void RtAudioDriver::stop()
  {
    adac.stopStream();
  }

  void RtAudioDriver::init_audio()
  {
    RtAudio::StreamOptions opts;
    opts.flags = RTAUDIO_SCHEDULE_REALTIME;
    opts.numberOfBuffers = 1;
    opts.streamName = "OTTO";
    unsigned samplerate = conf.sample_rate;
    adac.openStream(
      &o_params, &i_params, RTAUDIO_FLOAT32, samplerate, &buffer_size_,
      [](void* out, void* in, unsigned nframes, double time, RtAudioStreamStatus status, void* self_) {
        return static_cast<RtAudioDriver*>(self_)->rtaudio_cb(static_cast<float*>(out), static_cast<float*>(in),
                                                              static_cast<int>(nframes), time, status);
      },
      this, &opts);
    buffers.resize(buffer_size_ * 4);
    LOGI("Buffer size: {}", buffer_size_);
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
    OTTO_ASSERT(callback != nullptr);
    callback(cbd);
    // Interleave audio
    for (int i = 0; i < nframes; i++) {
      out[i * 2] = cbd.output.left[i];
      out[i * 2 + 1] = cbd.output.right[i];
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
