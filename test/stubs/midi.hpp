#pragma once

#include "lib/midi.hpp"

namespace otto::stubs {

  struct StubMidiHandler : midi::MidiHandler {
    void handle(midi::NoteOn e) noexcept override
    {
      key_down[e.note] = true;
      events.emplace_back(e);
    }
    void handle(midi::NoteOff e) noexcept override
    {
      key_down[e.note] = false;
      events.emplace_back(e);
    }
    std::vector<variant> events;
    std::array<bool, 128> key_down = {false};
  };
} // namespace otto::stubs
