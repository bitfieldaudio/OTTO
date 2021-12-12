#include "audio.hpp"

#include <Gamma/Domain.h>

namespace otto::services {

  Audio::Audio(util::smart_ptr<drivers::IAudioDriver>&& d) : ExecutorProvider("audio"), driver_(std::move(d))
  {
    driver_->set_callback(std::bind_front(&Audio::loop_func, this));
    AudioDomain::buffer_pool_ = util::AudioBufferPool{16, driver_->buffer_size()};
    gam::sampleRate(util::narrow<double>(driver_->sample_rate()));
    driver_->start();
  }

  util::at_exit Audio::set_midi_handler(util::smart_ptr<midi::IMidiHandler> h) noexcept
  {
    executor().execute([this, h = std::move(h)]() mutable { midi_.set_handler(std::move(h)); });
    executor().sync();
    return util::at_exit([this] {
      executor().execute([this] { midi_.set_handler(nullptr); });
      executor().sync();
    });
  }

  util::at_exit Audio::set_process_callback(Callback&& cb) noexcept
  {
    executor().execute([this, cb = std::move(cb)]() mutable { callback_ = std::move(cb); });
    executor().sync();
    return util::at_exit([this] {
      executor().execute([this] { callback_ = nullptr; });
      executor().sync();
    });
  }

  void Audio::loop_func(CallbackData data) noexcept
  {
    [[maybe_unused]] static int call_once = (log::set_thread_name("audio"), 0);
    midi_.process_events();
    if (callback_) {
      callback_(data);
    } else {
      data.output.clear();
    }
    executor().run_queued_functions();
    buffer_count_++;
  }

  unsigned Audio::buffer_count() noexcept
  {
    return buffer_count_;
  }

  void Audio::wait_for_n_buffers(int n) noexcept
  {
    unsigned start = buffer_count();
    while (buffer_count() <= (start + n)) {
      std::this_thread::sleep_for(chrono::nanoseconds((1ns / 1s) * driver_->buffer_size() / driver_->sample_rate()));
    }
  }

  drivers::MidiController& Audio::midi() noexcept
  {
    return midi_.controller();
  }
} // namespace otto::services
