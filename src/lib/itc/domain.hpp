#pragma once

#include "lib/logging.hpp"

#include "executor.hpp"

namespace otto::itc {
  /// Provide access to an executor. Inherit from this virtually
  struct IDomain {
    IDomain() noexcept = default;
    virtual ~IDomain() noexcept = default;
    virtual IExecutor& executor() = 0;
  };

  namespace detail {
    /// Use this trick to detect if `Domain` is a domain, even if it privately
    /// inherits from `IDomain`
    template<typename Domain>
    struct DomainTest : Domain, virtual IDomain {};
  } // namespace detail

  template<typename T>
  concept ADomain = !std::is_abstract_v<detail::DomainTest<T>>;

  /// Simply attach a domain to a class that needs it.
  ///
  /// Used for example when wanting to use a `Consumer` without deriving from it.
  template<ADomain Domain, typename Class>
  struct WithDomain : Domain, Class {
    using Class::Class;
  };

  namespace detail {
    // Declared in namespace scope instead of as a static member to make sure
    // we get a propper single definition.
    template<typename Tag = void>
    IExecutor* static_executor_ptr = nullptr; // NOLINT
  }                                           // namespace detail

  /// Domain which uses a static variable for the executor
  template<typename Tag = void>
  struct StaticDomain : virtual IDomain {
    using domain_tag_t = Tag;
    StaticDomain() = default;
    virtual ~StaticDomain() = default;

    static void set_static_executor(IExecutor& e)
    {
      detail::static_executor_ptr<Tag> = &e;
    }

    static void set_static_executor(IExecutor* e)
    {
      detail::static_executor_ptr<Tag> = e;
    }

    static IExecutor* get_static_executor()
    {
      return detail::static_executor_ptr<Tag>;
    }

    IExecutor& executor() override
    {
      return *get_static_executor();
    }
  };
} // namespace otto::itc
