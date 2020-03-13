#pragma once

#include <gsl/span>
#include <tl/optional.hpp>

#include "util/locked.hpp"
#include "util/thread.hpp"

#include "services/controller.hpp"
#include "util/serial.hpp"

#include "RtMidi.h"

#include "board/hardware_map.hpp"
#include "board/mcu_controller.hpp"

namespace otto::services {

  using namespace otto::board::controller;

  /// Communicates with the OTTO MCU over midi sysex
  ///
  /// Useful mainly for development
  struct MCUSysexController final : MCUController {
    using HardwareMap = board::controller::Proto1MCUHardwareMap;

    static constexpr chrono::duration sleep_time = chrono::milliseconds(20);
    MCUSysexController(int in_port = -1, int out_port = -1);

    template<typename Parser>
    void add_args(Parser& cli);

    static std::unique_ptr<Controller> make_or_dummy(int in_port = -1, int out_port = -1);
    static std::unique_ptr<Controller> make_or_emulator(int in_port = -1, int out_port = -1);

    static MCUSysexController& current()
    {
      return dynamic_cast<MCUSysexController&>(Controller::current());
    }

  protected:
    void queue_message(BytesView) override;

  private:
    void parse_midi_response(gsl::span<std::uint8_t>);

    util::double_buffered<std::vector<std::uint8_t>, util::clear_outer> write_buffer_;
    util::sleeper_thread midi_thread;

    RtMidiIn midi_in;
    RtMidiOut midi_out;
  };

} // namespace otto::services

// kak: other_file=../../src/controller.cpp
