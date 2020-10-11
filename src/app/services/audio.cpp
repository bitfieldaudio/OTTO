#include "audio.hpp"

#include <Gamma/Domain.h>

namespace otto::services {

  Audio::Audio(util::any_ptr<AudioDriver>::factory&& d) : driver_(d())
  {
    driver_->set_callback(std::bind_front(&Audio::loop_func, this));
    abp_ = util::AudioBufferPool{16, driver_->buffer_size()};
    gam::sampleRate(driver_->sample_rate());
    runtime->on_enter_stage(Runtime::Stage::running, [&d = *driver_] { d.start(); });
  }

  void Audio::set_midi_handler(util::any_ptr<midi::IMidiHandler> h) noexcept
  {
    midi_handler_ = std::move(h);
  }

  void Audio::enqueue_midi(midi::MidiEvent e) noexcept
  {
    midi_queue_.enqueue(std::move(e));
  }

  util::AudioBufferPool& Audio::buffer_pool() noexcept
  {
    OTTO_ASSERT(abp_.has_value());
    return *abp_;
  }

  void Audio::set_process_callback(Callback&& cb) noexcept
  {
    callback_ = std::move(cb);
  }

  void Audio::loop_func(CallbackData data) noexcept
  {
    midi::MidiEvent evt;
    for (int i = 0; i < 5; i++) {
      if (!midi_queue_.try_dequeue(evt)) break;
      midi_handler_->handle(evt);
    }
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
    while (buffer_count() <= (start + n))
      std::this_thread::sleep_for(chrono::nanoseconds((1ns / 1s) * driver_->buffer_size() / driver_->sample_rate()));
  }
} // namespace otto::services
