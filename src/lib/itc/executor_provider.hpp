#pragma once

#include <yamc_semaphore.hpp>

#include "lib/chrono.hpp"
#include "lib/itc/domain.hpp"
#include "lib/itc/executor.hpp"

namespace otto::itc {

  template<typename DomainTag>
  struct ExecutorProvider {
    using Domain = StaticDomain<DomainTag>;
    ExecutorProvider(util::string_ref domain_name)
    {
      if (Domain::get_static_executor() == nullptr) {
        Domain::set_static_executor(executor());
      }
      Domain::set_domain_name(domain_name.c_str());
    }
    virtual ~ExecutorProvider() noexcept
    {
      if (Domain::get_static_executor() == &executor()) {
        Domain::set_static_executor(nullptr);
      }
    }

    ExecutorProvider(const ExecutorProvider&) = delete;
    ExecutorProvider& operator=(const ExecutorProvider&) = delete;

    QueueExecutor& executor() noexcept
    {
      return executor_;
    }

    /// Block thread until all functions enqueued by this thread up to this point
    /// have been executed.
    void sync() noexcept
    {
      auto sem = yamc::binary_semaphore(0);
      executor_.execute([&sem] { sem.release(); });
      sem.acquire();
    }

    /// Block thread until all functions enqueued by this thread up to this point
    /// have been executed, with a timeout
    ///
    /// returns true if successfully synced
    [[nodiscard]] bool try_sync(chrono::duration d) noexcept
    {
      auto sem = std::make_unique<yamc::binary_semaphore>(0);
      auto* s = sem.get();
      executor_.execute([sem = std::move(sem)] { sem->release(); });
      return s->try_acquire_for(d);
    }

  private:
    QueueExecutor executor_;
  };

} // namespace otto::itc
