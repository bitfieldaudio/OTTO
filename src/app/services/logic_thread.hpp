#pragma once

#include "lib/core/service.hpp"
#include "lib/itc/executor.hpp"
#include "lib/itc/itc.hpp"

namespace otto::services {

  struct LogicThread : core::Service<LogicThread> {
    /// An {@ref itc::Consumer} with the executor hardcoded to `LogicThread::executor()`
    template<itc::AState State>
    struct Consumer;
    virtual itc::IExecutor& executor() noexcept = 0;

    static core::ServiceHandle<LogicThread> make_default();
  };


  template<itc::AState State>
  struct LogicThread::Consumer : itc::Consumer<State> {
    Consumer(itc::Channel<State>& c) : itc::Consumer<State>(c, logic->executor()) {}

  private:
    core::ServiceAccessor<LogicThread> logic;
  };
} // namespace otto::services
