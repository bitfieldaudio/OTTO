#pragma once

#include "lib/util/name_of.hpp"

#include "lib/logging.hpp"

#include "executor.hpp"

namespace otto::itc {
  struct DomainId {
    DomainId(const char* name) : data(name) {}
    auto operator<=>(const DomainId&) const noexcept = default;
    bool operator==(const DomainId&) const noexcept = default;

    friend std::ostream& operator<<(std::ostream& str, const DomainId& self)
    {
      return str << self.data;
    }

  private:
    const char* data;
  };

  /// Provide access to an executor. Inherit from this virtually
  struct IDomain {
    IDomain() noexcept = default;
    virtual ~IDomain() noexcept = default;
    virtual IExecutor& executor() = 0;
    virtual DomainId domain_id() = 0;
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

    template<typename Tag = void>
    const char* static_name_ptr = util::name_of<Tag>.c_str(); // NOLINT
  }                                                           // namespace detail

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

    static void set_domain_name(const char* n)
    {
      detail::static_name_ptr<Tag> = n;
    }

    static IExecutor* get_static_executor()
    {
      return detail::static_executor_ptr<Tag>;
    }

    static IExecutor& static_executor()
    {
      auto* exec = get_static_executor();
      if (exec == nullptr) {
        LOGE("Trying to get executor that is not available {}", detail::static_name_ptr<Tag>);
        std::terminate();
      }
      return *exec;
    }

    IExecutor& executor() override
    {
      return *get_static_executor();
    }

    DomainId domain_id() override
    {
      return DomainId{detail::static_name_ptr<Tag>};
    }
  };
} // namespace otto::itc
