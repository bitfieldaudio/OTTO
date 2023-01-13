#pragma once

#include "context.hpp"
#include "service.hpp"

namespace otto::itc {

  template<AService Service>
  struct Provider<Service> : detail::ProviderBase {
    Provider(Context& context) : context_(&context)
    {
      context.register_provider(this);
    }

    // Non-copyable
    Provider(const Provider&) = delete;
    Provider& operator=(const Provider&) = delete;

    ~Provider() noexcept
    {
      context_->unregister_provider(this);
    }

    /// The context this accessor is registered on
    [[nodiscard]] Context& context() const noexcept
    {
      return *context_;
    }

    /// The accessors this provider is currently linked to
    const std::vector<accessor_t<Service>*>& accessors() const noexcept
    {
      return accessors_;
    }

  private:
    friend linker;

    Context* context_;
    std::vector<accessor_t<Service>*> accessors_;
  };

  template<AService... Service>
  struct Provider : Provider<Service>... {
    /// The accessors this provider is currently linked to
    template<AService S>
    const std::vector<accessor_t<S>*>& accessors() const noexcept
    {
      return Provider<S>::accessors();
    }
  };

} // namespace otto::itc
