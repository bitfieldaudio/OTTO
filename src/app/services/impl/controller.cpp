#include "controller.hpp"

namespace otto::services {

  struct ExecutorWrapper : InputHandler {
    ExecutorWrapper(itc::IExecutor& executor, util::any_ptr<InputHandler>&& delegate)
      : executor_(executor), delegate_(std::move(delegate))
    {}

    void handle(const KeyPress& e) noexcept override
    {
      executor_.execute([h = delegate_.get(), e] { h->handle(e); });
    }
    void handle(const KeyRelease& e) noexcept override
    {
      executor_.execute([h = delegate_.get(), e] { h->handle(e); });
    }
    void handle(const EncoderEvent& e) noexcept override
    {
      executor_.execute([h = delegate_.get(), e] { h->handle(e); });
    }

  private:
    itc::IExecutor& executor_;
    util::any_ptr<InputHandler> delegate_;
  };

  MCUController::MCUController(util::any_ptr<MCUPort>&& port, Config::Handle conf)
    : conf_(std::move(conf)), com_(std::move(port)), thread_([this] {
        while (runtime->should_run()) {
          {
            std::unique_lock l(queue_mutex_);
            for (const auto& data : queue_) {
              com_.port_->write(data);
            }
            queue_.clear();
          }
          Packet p;
          do {
            p = com_.port_->read();
            com_.handle_packet(p);
          } while (p.cmd != Command::none);
          std::this_thread::sleep_for(conf_->wait_time);
        }
      })
  {}

  void MCUController::set_input_handler(InputHandler& h)
  {
    com_.handler = std::make_unique<ExecutorWrapper>(logic_thread->executor(), &h);
  }

  void MCUController::set_led_color(LED led, LEDColor c)
  {
    std::unique_lock l(queue_mutex_);
    queue_.push_back({Command::led_set, {util::enum_integer(led.key), c.r, c.g, c.b}});
  }

  MCUCommunicator::MCUCommunicator(util::any_ptr<MCUPort>&& com) : port_(std::move(com)) {}

  void MCUCommunicator::handle_packet(Packet p)
  {
    switch (p.cmd) {
      case Command::key_events: {
        std::span<std::uint8_t> presses = {p.data.data(), 8};
        std::span<std::uint8_t> releases = {p.data.data() + 8, 8};
        for (auto k : util::enum_values<Key>()) {
          if (util::get_bit(presses, util::enum_integer(k))) handler->handle(KeyPress{{k}});
          if (util::get_bit(releases, util::enum_integer(k))) handler->handle(KeyRelease{{k}});
        }
      } break;
      case Command::encoder_events: {
        for (auto e : util::enum_values<Encoder>()) {
          if (p.data[util::enum_integer(e)] == 0) continue;
          handler->handle(EncoderEvent{e, static_cast<std::int8_t>(p.data[util::enum_integer(e)])});
        }
      } break;
      default: break;
    }
  }
} // namespace otto::services
