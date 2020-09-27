#pragma once

#include <tl/optional.hpp>
#include "app/services/audio.hpp"
#include "app/services/runtime.hpp"

namespace otto::services {

  struct AudioImpl : Audio {
    void set_process_callback(Callback&& cb) noexcept override
    {
      callback_ = std::move(cb);
    }

    itc::IExecutor& executor() noexcept override
    {
      return executor_;
    }

    util::AudioBufferPool& buffer_pool() noexcept override
    {
      OTTO_ASSERT(abp_.has_value());
      return *abp_;
    }

    void enqueue_midi(midi::MidiEvent e) noexcept override
    {
      midi_queue_.enqueue(std::move(e));
    }

    void set_midi_handler(util::any_ptr<midi::IMidiHandler> h) noexcept override
    {
      midi_handler_ = std::move(h);
    }

  private:
    [[no_unique_address]] core::ServiceAccessor<Runtime> runtime;

  protected:
    void set_buffer_size(std::size_t bufsize)
    {
      abp_ = util::AudioBufferPool{16, bufsize};
    }

    Callback callback_ = nullptr;
    itc::QueueExecutor executor_;
    moodycamel::ConcurrentQueue<midi::MidiEvent> midi_queue_;
    util::any_ptr<midi::IMidiHandler> midi_handler_;
    tl::optional<util::AudioBufferPool> abp_ = tl::nullopt;
  };
} // namespace otto::services
