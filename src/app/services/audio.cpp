#include "audio.hpp"

#include <Gamma/Domain.h>

namespace otto::services {

  Audio::Audio(util::smart_ptr<drivers::IAudioDriver>&& d) : driver_(std::move(d))
  {
    driver_->set_callback(std::bind_front(&Audio::loop_func, this));
    AudioDomain::buffer_pool_ = util::AudioBufferPool{16, driver_->buffer_size()};
    gam::sampleRate(util::narrow(driver_->sample_rate()));
    driver_->start();
  }

  void Audio::set_midi_handler(util::smart_ptr<midi::IMidiHandler> h) noexcept
  {
    midi_.set_handler(std::move(h));
  }

  void Audio::set_process_callback(Callback&& cb) noexcept
  {
    callback_ = std::move(cb);
  }

  void Audio::loop_func(CallbackData data) noexcept
  {
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
