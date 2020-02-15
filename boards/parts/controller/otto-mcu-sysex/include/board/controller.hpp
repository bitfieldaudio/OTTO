#pragma once

#include <gsl/span>
#include <tl/optional.hpp>

#include "util/locked.hpp"
#include "util/thread.hpp"

#include "services/controller.hpp"
#include "util/serial.hpp"

#include "RtMidi.h"

namespace otto::services {

  using BytesView = gsl::span<const std::uint8_t>;
  class Command;

  struct InputData {
    std::array<std::uint8_t, 8> rows = {0};
    std::array<std::uint8_t, 4> encoders = {0};

    /// @param Callable: `void(Key, bool down_now)`
    template<typename Callable>
    void for_updated_keys(const InputData&, Callable&&);
  };

  /// Communicates with the OTTO MCU over midi sysex
  ///
  /// Useful mainly for development
  struct MCUSysexController final : Controller {
    static constexpr chrono::duration sleep_time = chrono::milliseconds(20);
    MCUSysexController(int in_port = -1, int out_port = -1);

    template<typename Parser>
    void add_args(Parser& cli);

    void set_color(LED, LEDColor) override;
    void flush_leds() override;
    void clear_leds() override;

    static std::unique_ptr<Controller> make_or_dummy(int in_port = -1, int out_port = -1);
    static std::unique_ptr<Controller> make_or_emulator(int in_port = -1, int out_port = -1);

    static MCUSysexController& current()
    {
      return dynamic_cast<MCUSysexController&>(Controller::current());
    }

  private:
    void handle_response(BytesView);
    void parse_midi_response(gsl::span<std::uint8_t>);
    void queue_message(BytesView);

    void handle_keyevent(Command cmd, BytesView args, bool do_send_midi);

    InputData last_input_data;
    util::double_buffered<std::vector<std::uint8_t>, util::clear_outer> write_buffer_;
    util::sleeper_thread midi_thread;
    bool send_midi_ = true;
    util::enum_map<Key, std::pair<LEDColor, bool>> led_colors;

    RtMidiIn midi_in;
    RtMidiOut midi_out;
  };

} // namespace otto::services

// kak: other_file=../../src/controller.cpp
