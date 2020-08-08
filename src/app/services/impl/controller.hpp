#pragma once

#include <ranges>
#include <span>
#include <tl/optional.hpp>

#include "lib/util/any_ptr.hpp"
#include "lib/util/exception.hpp"

#include "app/services/controller.hpp"
#include "app/services/logic_thread.hpp"

namespace otto::services {

  struct MCUCommunicator {
    virtual ~MCUCommunicator() = default;

    /// Block until the next array of bytes is ready
    ///
    /// The data in the resulting span is valid until the next call to `get_next`.
    virtual std::span<std::uint8_t> read() = 0;
  };

  /// Describes the key matrix and LED order.
  struct HardwareMap {
    virtual ~HardwareMap() noexcept = default;
    virtual int row_count() const noexcept = 0;
    virtual int col_count() const noexcept = 0;
    virtual tl::optional<Key> key_at(std::uint8_t row, std::uint8_t col) const noexcept = 0;
    virtual std::uint8_t led_for(Key) const noexcept = 0;
  };

  struct MCUController final : Controller {
    explicit MCUController(util::any_ptr<MCUCommunicator>&& com, util::any_ptr<HardwareMap>&& hw)
      : com_(std::move(com)), hw_(std::move(hw))
    {
      old_data_.resize(hw_->row_count() + 4);
    }

    void set_input_handler(InputHandler& h) override
    {
      handler_ = &h;
    }

    void read_data()
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

  private:
    std::vector<std::uint8_t> old_data_;
    util::any_ptr<MCUCommunicator> com_;
    util::any_ptr<HardwareMap> hw_;
    InputHandler* handler_ = nullptr;
    [[no_unique_address]] core::ServiceAccessor<services::LogicThread> logic_thread;
  };

} // namespace otto::services
