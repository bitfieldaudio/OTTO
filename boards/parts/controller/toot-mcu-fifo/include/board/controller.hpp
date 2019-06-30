#pragma once

#include <gsl/span>

#include "util/locked.hpp"
#include "util/thread.hpp"

#include "services/controller.hpp"
#include "util/fifo.hpp"

namespace otto::services {

  using BytesView = gsl::span<const std::uint8_t>;
  class Command;

  struct TOOT_MCU_FIFO_Controller final : Controller {
    TOOT_MCU_FIFO_Controller();

    void set_color(LED, LEDColor) override;
    void flush_leds() override;
    void clear_leds() override;

    static std::unique_ptr<Controller> make_or_dummy();

  private:
    void handle_message(BytesView);
    void queue_message(BytesView);

    void insert_key_event(Command cmd, Key key);
    void insert_key_or_midi(Command cmd, BytesView args, bool do_send_midi);

    util::FIFO fifo = {"/dev/toot-mcu-fifo"};
    util::double_buffered<EventBag, util::clear_inner> events_;
    util::double_buffered<std::vector<std::uint8_t>, util::clear_outer> write_buffer_;
    util::thread read_thread;
    bool send_midi_ = true;
  };

} // namespace otto::services

// kak: other_file=../../src/controller.cpp