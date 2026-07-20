#pragma once

#include <optional>
#include <RtMidi.h>

#include "lib/util/algorithm.hpp"

#include "lib/logging.hpp"
#include "lib/midi.hpp"

#include "app/services/audio.hpp"
#include "app/services/config.hpp"

namespace otto {

  struct MidiDriverConfig : Config<MidiDriverConfig> {
    static constexpr util::string_ref name = "MidiDriver";
    /// "none" = virtual port only (default — safe on macOS with many devices).
    /// Empty string = first suitable hardware port.
    /// Otherwise = exact RtMidi port name.
    std::string input_port =
#if defined(__APPLE__)
      "none"
#else
      ""
#endif
      ;
    DECL_VISIT(input_port)
  };

  struct RtMidiDriver {
    RtMidiDriver(drivers::MidiController& midi, const MidiDriverConfig& conf = {}) : midi_(midi)
    {
      try {
        midi_in_.openVirtualPort("OTTO in");
        LOGI("Opened virtual MIDI port 'OTTO in'");
      } catch (const RtMidiError& e) {
        LOGW("Could not open virtual MIDI port: {}", e.getMessage());
      }

      LOGI("Available MIDI ports:");
      for (auto i = 0U; i < midi_in_.getPortCount(); i++) {
        LOGI(" - '{}'", midi_in_.getPortName(i));
      }

      auto port_index = pick_port(conf.input_port);
      if (port_index) {
        try {
          midi_in_.openPort(*port_index, "OTTO input");
          LOGI("Connected to MIDI port '{}'", midi_in_.getPortName(*port_index));
        } catch (const RtMidiError& e) {
          LOGW("Failed to open MIDI port: {}", e.getMessage());
        }
      } else {
        LOGI("Using virtual MIDI input only (set MidiDriver.input_port to select a device)");
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

    static bool is_ignored_port(std::string_view port_name)
    {
      return util::starts_with(port_name, "Midi Through:Midi Through") || //
             util::starts_with(port_name, "OTTO ");
    }

    /// Pick a single hardware port index, or nullopt for virtual-only.
    std::optional<unsigned> pick_port(std::string_view wanted)
    {
      if (wanted == "none") return std::nullopt;

      if (!wanted.empty()) {
        for (auto i = 0U; i < midi_in_.getPortCount(); i++) {
          if (midi_in_.getPortName(i) == wanted) return i;
        }
        LOGW("Configured MIDI port '{}' not found", wanted);
        return std::nullopt;
      }

      // Auto: first non-ignored hardware port
      for (auto i = 0U; i < midi_in_.getPortCount(); i++) {
        auto name = midi_in_.getPortName(i);
        if (!is_ignored_port(name)) return i;
      }
      return std::nullopt;
    }

  private:
    drivers::MidiController& midi_;
    RtMidiIn midi_in_ = {RtMidi::Api::UNSPECIFIED, "OTTO"};
  };
} // namespace otto
