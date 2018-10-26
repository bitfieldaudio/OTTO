#pragma once

namespace otto::core {

  struct Service {
    Service() = default;
    virtual ~Service() = default;

    Service(const Service&) = delete;
    Service(Service&&) = delete;
    auto operator=(const Service&) = delete;
    auto operator=(Service&&) = delete;
  };

} // namespace otto::core
