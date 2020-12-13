#pragma once

#include <vector>
#include "app/input.hpp"
#include "lib/util/smart_ptr.hpp"

namespace otto {

  struct EventDistributor : IInputHandler {
    void handle(KeyPress e) noexcept override
    {
      for (auto& handler : handlers_) handler->handle(e);
    }
    void handle(KeyRelease e) noexcept override
    {
      for (auto& handler : handlers_) handler->handle(e);
    }
    void handle(EncoderEvent e) noexcept override
    {
      for (auto& handler : handlers_) handler->handle(e);
    }

    IInputHandler& add_handler(util::smart_ptr<IInputHandler> ha)
    {
      return *handlers_.emplace_back(std::move(ha));
    }

    template<std::derived_from<IInputHandler> H>
    H& add_handler(util::smart_ptr<H> ha)
    {
      auto& res = *ha;
      handlers_.emplace_back(std::move(ha));
      return res;
    }

    template<std::derived_from<IInputHandler> H>
    H& add_handler(std::unique_ptr<H> ha)
    {
      return add_handler(util::smart_ptr<H>(std::move(ha)));
    }

    template<std::derived_from<IInputHandler> H>
    H& add_handler(H* ha)
    {
      return add_handler(util::smart_ptr<H>(ha));
    }

  private:
    std::vector<util::smart_ptr<IInputHandler>> handlers_;
  };
} // namespace otto
