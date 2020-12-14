#pragma once

#include <RtMidi.h>
#include "app/services/audio.hpp"
#include "lib/core/service.hpp"
#include "lib/logging.hpp"
#include "lib/midi.hpp"
#include "lib/util/algorithm.hpp"

namespace otto {

  struct RtMidiDriver {
    RtMidiDriver()
    {
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
            self.audio->enqueue_midi(e);
          } catch (std::exception& e) {
            LOGE("{}", e.what());
          }
        },
        this);
    }

    static bool should_connect_to(std::string_view port_name)
    {
      return !util::starts_with(port_name, "Midi Through:Midi Through");
    }

  private:
    [[no_unique_address]] core::ServiceAccessor<services::Audio> audio;
    RtMidiIn midi_in_ = {RtMidi::Api::UNSPECIFIED, "OTTO"};
  };
} // namespace otto
