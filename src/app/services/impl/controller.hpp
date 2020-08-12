#pragma once

#include <ranges>
#include <span>
#include <tl/optional.hpp>

#include "app/services/runtime.hpp"
#include "lib/util/any_ptr.hpp"
#include "lib/util/exception.hpp"

#include "app/services/controller.hpp"
#include "app/services/logic_thread.hpp"

namespace otto::services {

  struct MCUPort {
    virtual ~MCUPort() = default;

    virtual std::size_t write(std::span<std::uint8_t> data) = 0;

    /// Block until the next array of bytes is ready
    ///
    /// The data in the resulting span is valid until the next call to `get_next`.
    virtual std::span<std::uint8_t> read(std::size_t count) = 0;
  };

  /// Describes the key matrix and LED order.
  struct HardwareMap {
    virtual ~HardwareMap() noexcept = default;
    virtual int row_count() const noexcept = 0;
    virtual int col_count() const noexcept = 0;
    virtual tl::optional<Key> key_at(std::uint8_t row, std::uint8_t col) const noexcept = 0;
    virtual std::uint8_t led_for(Key) const noexcept = 0;
  };

  /// Communicates with the mcu, parsing data etc.
  ///
  /// Does the bulk of the work of {@ref MCUController}, but is separated out
  /// to allow usage/testing of the individual methods
  struct MCUCommunicator {
    MCUCommunicator(util::any_ptr<MCUPort>&& port, util::any_ptr<HardwareMap>&& hw);

    void request_input()
    {
      std::array<std::uint8_t, 1> data = {1};
      com_->write(data);
      read_input_response();
    }

    /// Read input data from MCUCommunicator and send events.
    ///
    /// @throws util::exception if the data is invalid.
    void read_input_response();

    util::any_ptr<InputHandler> handler = nullptr;

  private:
    std::vector<std::uint8_t> old_data_;
    util::any_ptr<MCUPort> com_;
    util::any_ptr<HardwareMap> hw_;
  };

  struct MCUController final : Controller {
    static constexpr chrono::duration wait_time = 20ms;
    explicit MCUController(util::any_ptr<MCUPort>&& com, util::any_ptr<HardwareMap>&& hw);
    void set_input_handler(InputHandler& h) override;

  private:
    MCUCommunicator com_;
    [[no_unique_address]] core::ServiceAccessor<services::Runtime> runtime;
    [[no_unique_address]] core::ServiceAccessor<services::LogicThread> logic_thread;
    std::jthread thread_;
  };

} // namespace otto::services
