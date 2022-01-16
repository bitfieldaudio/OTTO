#pragma once

#include <queue>

#include "app/services/controller.hpp"

namespace otto::test {
  struct StubMCUPort final : drivers::MCUPort {
    void write(const drivers::Packet& p) override
    {
      OTTO_UNREACHABLE();
    }

    tl::optional<drivers::Packet> read() override
    {
      if (data.empty()) return {};
      auto res = data.front();
      data.pop();
      return res;
    }

    void stop() override {}

    std::queue<drivers::Packet> data;
  };
} // namespace otto::test
