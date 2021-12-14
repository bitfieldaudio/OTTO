#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "lib/util/concepts.hpp"
#include "lib/util/exception.hpp"
#include "lib/util/name_of.hpp"
#include "lib/util/ranges.hpp"
#include "lib/util/serialization.hpp"

#include "service.hpp"

namespace otto::itc {

  /// Helper struct to make friendship for link helper functions easier
  struct linker {
    template<AService S>
    static void link(Provider<S>& p, Accessor<S>& a)
    {
      if (a.provider_ != nullptr) {
        unlink(*a.provider_, a);
      }
      // Since this is called from the Accessor constructor, it is called
      // before `accessor_t` is constructed. Thus, this cast is detected by
      // UBsan, and can technically result in an ilegal access, if the
      // Accessor is accessed by the provider before it is fully constructed.
      // Hence, this is a reinterpret_cast instead of a static_cast.
      p.accessors_.emplace_back(reinterpret_cast<accessor_t<S>*>(&a));
      a.provider_ = &p;
    }

    template<AService S>
    static void unlink(Provider<S>& p, Accessor<S>& a)
    {
      std::erase_if(p.accessors_, [&](auto* ptr) { return ptr == &a; });
      a.provider_ = nullptr;
    }
  };

  /// A context tree where providers and accessors of any service can be created and accessed
  struct Context {
    Context() = default;
    ~Context() = default;

    Context(Context&&) = default;
    Context& operator=(Context&&) = default;

    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    /// Access or create a nested channel group by name
    Context& operator[](std::string_view sv)
    {
      // Apparently transparent keys don't work in gcc for string_view/string
      // TODO: Look into that ^
      auto found = children_.find(std::string(sv));
      if (found == children_.end()) {
        auto [iter, inserted] = children_.emplace(sv, std::make_unique<Context>());
        iter->second->parent_ = this;
        found = iter;
      }
      return *found->second;
    }

    /// Walk up the tree to find the nearest provider of a service
    template<AService S>
    provider_t<S>* find_provider()
    {
      auto res = provider_of<S>();
      if (res != nullptr) return res;
      if (parent_ != nullptr) {
        return parent_->find_provider<S>();
      }
      return nullptr;
    }

    const Context* parent() const noexcept
    {
      return parent_;
    }
    const auto& children() const noexcept
    {
      return children_;
    }
    const auto& providers() const noexcept
    {
      return providers_;
    }
    const auto& accessors() const noexcept
    {
      return accessors_;
    }

    template<AService S>
    provider_t<S>* provider_of() const noexcept
    {
      auto found = providers_.find(key_of<S>());
      if (found != providers_.end()) {
        return static_cast<provider_t<S>*>(found->second);
      }
      return nullptr;
    }

    template<AService S>
    auto accessors_of() const noexcept
    {
      return util::equal_range(accessors_, key_of<S>());
    }

  private:
    template<AService...>
    friend struct Provider;
    template<AService...>
    friend struct Accessor;

    template<AService S>
    static constexpr util::string_ref key_of() noexcept
    {
      return util::qualified_name_of<S>;
    }

    /// Called from Provider constructor
    template<AService S>
    void register_provider(Provider<S>* provider)
    {
      auto [iter, inserted] = providers_.emplace(key_of<S>(), provider);
      if (!inserted) {
        throw util::exception("Existing provider found for event {}", key_of<S>());
      }
      register_provider_recurse(provider);
    }
    template<AService S>
    void register_provider_recurse(Provider<S>* provider)
    {
      for (auto [k, r] : util::equal_range(accessors_, key_of<S>())) {
        linker::link(*provider, *static_cast<Accessor<S>*>(r));
      }
      for (auto&& [k, child] : children_) {
        child->register_provider_recurse(provider);
      }
    }

    template<AService S>
    void unregister_provider(Provider<S>* provider)
    {
      auto found = std::ranges::find(providers_, provider, [](auto& pair) { return pair.second; });
      providers_.erase(found);
      for (Accessor<S>* r : provider->accessors()) {
        linker::unlink(*provider, *r);
      }
    }

    template<AService S>
    void register_accessor(Accessor<S>* accessor)
    {
      accessors_.emplace(key_of<S>(), accessor);
      auto* s = find_provider<S>();
      if (s) linker::link(*s, *accessor);
    }

    template<AService S>
    void unregister_accessor(Accessor<S>* accessor)
    {
      auto accessors = util::equal_range(accessors_, key_of<S>());
      auto found = std::ranges::find(accessors, accessor, [](auto& pair) { return pair.second; });
      if (found != accessors.end()) accessors_.erase(found);
      if (accessor->provider()) {
        linker::unlink(*accessor->provider(), *accessor);
      }
    }

    Context* parent_ = nullptr;
    std::unordered_map<std::string, std::unique_ptr<Context>> children_;
    std::unordered_map<util::string_ref, detail::ProviderBase*> providers_;
    std::unordered_multimap<util::string_ref, detail::AccessorBase*> accessors_;
  };

} // namespace otto::itc

namespace otto::util {

  template<>
  struct serialize_impl<itc::Context> {
    static void serialize_into(json::value& json, const itc::Context& ctx)
    {
      for (auto&& [key, prov] : ctx.providers()) {
        if (const auto* ser = dynamic_cast<util::ISerializable*>(prov)) {
          util::serialize_into(json[key.c_str()], *ser);
        }
      }
      for (auto&& [k, v] : ctx.children()) {
        util::serialize_into(json[k.c_str()], *v);
      }
    }

    static void deserialize_from(const json::value& json, itc::Context& ctx)
    {
      for (auto&& [key, prov] : ctx.providers()) {
        if (auto* ser = dynamic_cast<util::ISerializable*>(prov)) {
          util::deserialize_from_member(json, key.c_str(), *ser);
        }
      }
      for (auto&& [k, v] : ctx.children()) {
        util::deserialize_from_member(json, k, *v);
      }
    }
  };

} // namespace otto::util
