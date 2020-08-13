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

  MCUController::MCUController(util::any_ptr<MCUPort>&& port, util::any_ptr<HardwareMap>&& hw, Config conf)
    : conf_(std::move(conf)), com_(std::move(port), std::move(hw)), thread_([this] {
        while (runtime->should_run()) {
          std::array<std::uint8_t, 1> data = {0};
          com_.port_->write(data);
          std::this_thread::sleep_for(conf_.wait_time);
          com_.read_input_response();
          std::this_thread::sleep_for(conf_.wait_time);
        }
      })
  {}

  MCUController::MCUController(util::any_ptr<MCUPort>&& port, util::any_ptr<HardwareMap>&& hw)
    : MCUController(std::move(port), std::move(hw), core::ServiceAccessor<ConfigManager>()->register_config<Config>())
  {}

  void MCUController::set_input_handler(InputHandler& h)
  {
    com_.handler = std::make_unique<ExecutorWrapper>(logic_thread->executor(), &h);
  }

  MCUCommunicator::MCUCommunicator(util::any_ptr<MCUPort>&& com, util::any_ptr<HardwareMap>&& hw)
    : port_(std::move(com)), hw_(std::move(hw))
  {
    old_data_.resize(hw_->row_count() + 4);
  }

  void MCUCommunicator::read_input_response()
  {
    auto nrows = hw_->row_count();
    auto ncols = hw_->col_count();
    std::span data = port_->read(nrows + 4);
    if (data.empty()) return;
    if (data.size() != nrows + 4)
      throw util::exception("Data had invalid length. Got {} bytes, expected {}", data.size(), nrows + 4);
    if (!handler) return;
    for (int r = 0; r < data.size(); r++) {
      for (int c = 0; c < ncols; c++) {
        auto key = hw_->key_at(r, c);
        if (!key) continue;
        if ((data[r] & (1 << c)) == (old_data_[r] & (1 << c))) continue;
        if (data[r] & (1 << c)) {
          handler->handle(KeyPress{*key});
        } else {
          handler->handle(KeyRelease{*key});
        }
      }
    }
    for (int i = 0; i < 4; i++) {
      auto didx = i + nrows;
      if (old_data_[didx] == data[didx]) continue;
      auto enc = *util::enum_cast<Encoder>(i);
      int val = data[didx] - old_data_[didx];
      // Handle rollover correctly
      if (std::abs(val) > 127) val -= std::copysign(256, val);
      handler->handle(EncoderEvent{enc, val});
    }
    std::ranges::copy(data, old_data_.begin());
  }
} // namespace otto::services
