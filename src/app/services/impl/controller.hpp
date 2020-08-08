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
    explicit MCUController(util::any_ptr<MCUCommunicator>&& com, util::any_ptr<HardwareMap>&& hw);
    void set_input_handler(InputHandler& h) override;

    /// Read input data from MCUCommunicator and send events.
    /// 
    /// @throws util::exception if the data is invalid.
    void read_input_data();

  private:
    std::vector<std::uint8_t> old_data_;
    util::any_ptr<MCUCommunicator> com_;
    util::any_ptr<HardwareMap> hw_;
    InputHandler* handler_ = nullptr;
    [[no_unique_address]] core::ServiceAccessor<services::LogicThread> logic_thread;
  };

} // namespace otto::services
