#pragma once

#include <thread>

#include "lib/chrono.hpp"

#include "app/drivers/audio_driver.hpp"
#include "app/services/runtime.hpp"

namespace otto::stubs {
  struct DummyAudioMixer final : drivers::IAudioMixer {
    void set_volume(float) override{

    };
    [[nodiscard]] float get_volume() const override
    {
      return 1.f;
    };
  };

  struct NoProcessAudioDriver final : drivers::IAudioDriver {
    void set_callback(Callback&& cb) override
    {
      callback = std::move(cb);
    }
    void start() override {}
    void stop() override {}
    [[nodiscard]] std::size_t buffer_size() const override
    {
      return 64;
    }
    [[nodiscard]] std::size_t sample_rate() const override
    {
      return 44100;
    }

    DummyAudioMixer& mixer() override
    {
      return mixer_;
    }

    Callback callback;
    DummyAudioMixer mixer_;
  };

  struct DummyAudioDriver final : drivers::IAudioDriver {
    DummyAudioDriver()
    {
      buffers_.resize(buffer_size() * 4);
    }
    void set_callback(Callback&& cb) override
    {
      callback_ = std::move(cb);
    }
    void start() override
    {
      thread_ = std::jthread([this](const std::stop_token& stopper) {
        auto input_buf = util::stereo_audio_buffer(
          util::audio_buffer(std::span(buffers_.data() + 0 * buffer_size(), buffer_size()), nullptr),
          util::audio_buffer(std::span(buffers_.data() + 1 * buffer_size(), buffer_size()), nullptr));
        auto output_buf = util::stereo_audio_buffer(
          util::audio_buffer(std::span(buffers_.data() + 2 * buffer_size(), buffer_size()), nullptr),
          util::audio_buffer(std::span(buffers_.data() + 3 * buffer_size(), buffer_size()), nullptr));
        CallbackData cbd = {
          .input = input_buf,
          .output = output_buf,
        };
        while (!stopper.stop_requested()) {
          callback_(cbd);
          std::this_thread::sleep_for(chrono::nanoseconds((1ns / 1s) * buffer_size() / sample_rate()));
        }
      });
    }
    void stop() override
    {
      thread_.request_stop();
      if (thread_.joinable()) thread_.join();
    }
    [[nodiscard]] std::size_t buffer_size() const override
    {
      return 64;
    }
    [[nodiscard]] std::size_t sample_rate() const override
    {
      return 44100;
    }

    DummyAudioMixer& mixer() override
    {
      return mixer_;
    }

  private:
    std::vector<float> buffers_;
    Callback callback_;
    std::jthread thread_;
    DummyAudioMixer mixer_;
  };

} // namespace otto::stubs
