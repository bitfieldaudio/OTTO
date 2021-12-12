#pragma once

#include <RtMidi.h>

#include "lib/util/algorithm.hpp"

#include "lib/logging.hpp"
#include "lib/midi.hpp"

#include "app/services/audio.hpp"

namespace otto {

  struct RtMidiDriver {
    RtMidiDriver(drivers::MidiController& midi) : midi_(midi)
    {
      midi_in_.openVirtualPort("OTTO in");
      for (auto i = 0U; i < midi_in_.getPortCount(); i++) {
        auto port = midi_in_.getPortName(i);
        LOGI("Found midi port {}", port);
        if (should_connect_to(port)) {
          midi_in_.openPort(i, "OTTO input");
          LOGI("Connected to midi port {}", port);
        }
      }

      midi_in_.setCallback(
        [](double timestamp, std::vector<std::uint8_t>* message, void* userdata) {
          auto& self = *static_cast<RtMidiDriver*>(userdata);
          try {
            auto e = midi::from_bytes(*message);
            self.midi_.send_event(e);
          } catch (std::exception& e) {
            LOGW("{}", e.what());
          }
        },
        this);
    }

    static bool should_connect_to(std::string_view port_name)
    {
      return !util::starts_with(port_name, "Midi Through:Midi Through");
    }

  private:
    drivers::MidiController& midi_;
    RtMidiIn midi_in_ = {RtMidi::Api::UNSPECIFIED, "OTTO"};
  };
} // namespace otto
