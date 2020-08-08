#include "controller.hpp"

namespace otto::services {

  MCUController::MCUController(util::any_ptr<MCUCommunicator>&& com, util::any_ptr<HardwareMap>&& hw)
    : com_(std::move(com)), hw_(std::move(hw))
  {
    old_data_.resize(hw_->row_count() + 4);
  }

  void MCUController::set_input_handler(InputHandler& h)
  {
    handler_ = &h;
  }

  void MCUController::read_input_data()
  {
    std::span data = com_->read();
    if (data.size() != hw_->row_count() + 4)
      throw util::exception("Data had invalid length. Got {} bytes, expected {}", data.size(), hw_->row_count() + 4);
    for (int r = 0; r < data.size(); r++) {
      for (int c = 0; c < hw_->col_count(); c++) {
        auto key = hw_->key_at(r, c);
        if (!key) continue;
        if ((data[r] & (1 << c)) == (old_data_[r] & (1 << c))) continue;
        if (data[r] & (1 << c)) {
          logic_thread->executor().execute([h = handler_, k = *key] { h->handle(KeyPress{k}); });
        } else {
          logic_thread->executor().execute([h = handler_, k = *key] { h->handle(KeyRelease{k}); });
        }
      }
    }
    for (int i = 0; i < 4; i++) {
      auto didx = i + hw_->row_count();
      if (old_data_[didx] == data[didx]) continue;
      auto enc = *util::enum_cast<Encoder>(i);
      int val = data[didx] - old_data_[didx];
      // Handle rollover correctly
      if (std::abs(val) > 127) val -= std::copysign(256, val);
      logic_thread->executor().execute([h = handler_, enc, val] { h->handle(EncoderEvent{enc, val}); });
    }
    std::ranges::copy(data, old_data_.begin());
  }
} // namespace otto::services
