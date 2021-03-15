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
      p.accessors_.emplace_back(static_cast<accessor_t<S>*>(&a));
      a.provider_ = static_cast<provider_t<S>*>(&p);
    }

    template<AService S>
    static void unlink(Provider<S>& p, Accessor<S>& a)
    {
      std::erase(p.accessors_, static_cast<accessor_t<S>*>(&a));
      a.provider_ = nullptr;
    }
  };

  /// A context tree where providers and accessors of any service can be created and accessed
  struct Context : util::ISerializable {
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
      auto found = providers_.find(key_of<S>());
      if (found != providers_.end()) {
        return static_cast<provider_t<S>*>(found->second);
      }
      if (parent_ != nullptr) {
        return parent_->find_provider<S>();
      }
      return nullptr;
    }

    void serialize_into(json::value&) const override {}
    void deserialize_from(const json::value&) override {}

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
