#pragma once

#include <memory>
#include <memory_resource>
#include <vector>

#include "lib/util/utility.hpp"

namespace otto::util {

  template<typename T, typename Metadata>
  struct RegistryEntry {
    RegistryEntry(util::function_ptr<std::unique_ptr<T>()> c, Metadata m) : constructor(c), metadata(std::move(m)) {}
    util::function_ptr<std::unique_ptr<T>()> constructor;
    Metadata metadata;
  };

  template<typename T, typename Metadata>
  struct Registry {
    using Entry = RegistryEntry<T, Metadata>;

    auto begin() const noexcept
    {
      return entries_.begin();
    }
    auto end() const noexcept
    {
      return entries_.end();
    }

    template<std::derived_from<T> U>
    [[nodiscard("The result of this function should be used to initialize a static variable")]] //
    bool
    add(Metadata md)
    {
      entries_.emplace_back([]() -> std::unique_ptr<T> { return std::make_unique<U>(); }, std::move(md));
      return true;
    }

  private:
    std::pmr::vector<Entry> entries_;
  };

  template<typename T, typename Metadata, typename Tag = void>
  struct StaticRegistry {
    using Entries = util::Registry<T, Metadata>;
    using Entry = typename Entries::Entry;

    template<std::derived_from<T> U>
    [[nodiscard("The result of this function should be used to initialize a static variable")]] //
    static bool
    add(Metadata md)
    {
      return get().template add<U>(std::move(md));
    }

    static Entries& get() noexcept
    {
      static Entries instance_;
      return instance_;
    }
  };

} // namespace otto::util
