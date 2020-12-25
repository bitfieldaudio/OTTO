#pragma once

#include <bitset>

#include <concurrentqueue.h>

#include "lib/util/smart_ptr.hpp"

#include "lib/midi.hpp"

namespace otto::drivers {

  struct MidiController {
    void send_event(midi::MidiEvent e) noexcept
    {
      midi_queue_.enqueue(e);
    }

    const std::bitset<128>& key_states() noexcept
    {
      return key_states_;
    }

  protected:
    MidiController() = default;
    moodycamel::ConcurrentQueue<midi::MidiEvent> midi_queue_;
    util::smart_ptr<midi::IMidiHandler> midi_handler_;
    std::bitset<128> key_states_;
  };

  struct MidiDriver : private MidiController {
    void set_handler(util::smart_ptr<midi::IMidiHandler> h) noexcept
    {
      midi_handler_ = std::move(h);
    }

    MidiController& controller()
    {
      return *this;
    }

    void process_events(int max = -1)
    {
      midi::MidiEvent evt;
      for (unsigned i = 0; max < 0 || i < max; i++) {
        if (!midi_queue_.try_dequeue(evt)) break;
        std::visit(util::overloaded([&](midi::NoteOn& e) { key_states_[e.note] = true; },
                                    [&](midi::NoteOff& e) { key_states_[e.note] = false; }, //
                                    [](auto&&) {}),
                   evt);
        if (midi_handler_) midi_handler_->handle(evt);
      }
    }
  };

} // namespace otto::drivers
