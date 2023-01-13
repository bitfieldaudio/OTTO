#pragma once

#include "context.hpp"
#include "service.hpp"

namespace otto::itc {

  template<AService Service>
  struct Accessor<Service> : detail::AccessorBase {
    Accessor(Context& ctx) : context_(&ctx)
    {
      ctx.register_accessor(this);
    }

    Accessor(const Accessor&) = delete;
    Accessor& operator=(const Accessor&) = delete;

    virtual ~Accessor() noexcept
    {
      unregister();
    }

    /// The context this accessor is registered on
    [[nodiscard]] Context& context() const noexcept
    {
      return *context_;
    }

    provider_t<Service>* provider() const noexcept
    {
      return static_cast<provider_t<Service>*>(provider_);
    }

  protected:
    /// Unregister from channel, and unlink from provider
    ///
    /// Runs automatically on destruction, but can be called
    /// manually when needed
    void unregister()
    {
      context_->unregister_accessor(this);
    }

  private:
    friend struct linker;

    Context* context_;
    Provider<Service>* provider_ = nullptr;
  };

  template<AService... Services>
  struct Accessor : Accessor<Services>... {
    Accessor(Context& ctx) : Accessor<Services>(ctx)... {}
  };
} // namespace otto::itc
