#pragma once

#include "app/services/runtime.hpp"
#include "lib/core/service.hpp"
#include "lib/itc/executor.hpp"
#include "lib/itc/executor_provider.hpp"
#include "lib/itc/itc.hpp"

namespace otto::services {

  struct LogicThread : core::Service<LogicThread>, itc::ExecutorProvider {
    /// An {@ref itc::Consumer} with the executor hardcoded to `LogicThread::executor()`
    template<itc::AState State>
    struct Consumer;

    LogicThread();

  private:
    [[no_unique_address]] core::ServiceAccessor<Runtime> runtime;
    std::jthread thread_;
  };


  template<itc::AState State>
  struct LogicThread::Consumer : itc::Consumer<State> {
    Consumer(itc::Channel<State>& c) : itc::Consumer<State>(c, logic->executor()) {}

  private:
    core::ServiceAccessor<LogicThread> logic;
  };
} // namespace otto::services
