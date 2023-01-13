#pragma once

#include <concepts>

#include "lib/util/local_vector.hpp"
#include "lib/util/serialization.hpp"
#include "lib/util/spin_lock.hpp"

#include "lib/itc/domain.hpp"
#include "lib/itc/executor.hpp"
#include "lib/itc/services/accessor.hpp"
#include "lib/itc/services/context.hpp"
#include "lib/itc/services/provider.hpp"
#include "lib/itc/services/service.hpp"

namespace otto::itc {

  struct PersistanceProvider;

  struct Persistant;

  struct persistance_service {
    using provider_t = PersistanceProvider;
    using accessor_t = Persistant;
  };

  /// An object extending this will be serialized into the available PersistanceProvider.
  struct Persistant : Accessor<persistance_service>, util::ISerializable {
    Persistant(Context& ctx, util::string_ref name) : Accessor(ctx), name_(name) {}

    [[nodiscard]] util::string_ref name() const
    {
      return name_;
    }

  private:
    util::string_ref name_;
  };

  /// This provider is able to serialize all Persistant objects in the context hierarchy.
  struct PersistanceProvider final : Provider<persistance_service>, util::ISerializable {
    using Provider::Provider;

    void serialize_into(json::value& json) const override
    {
      serialize_accessors_in(this->context(), json, this->accessors().size());
    }

    void deserialize_from(const json::value& json) override
    {
      deserialize_accessors_from(this->context(), json, this->accessors().size());
    }

  private:
    std::size_t serialize_accessors_in(const Context& ctx, json::value& json, std::size_t remaining) const
    {
      if (remaining == 0) return remaining;
      for (const auto& [key, v] : ctx.accessors_of<persistance_service>()) {
        const auto& acc = dynamic_cast<const Persistant&>(*v);
        if (acc.provider() == this) {
          util::serialize_into(json[acc.name()], acc);
          remaining--;
          if (remaining == 0) return remaining;
        }
      }

      for (const auto& [key, v] : ctx.children()) {
        remaining = serialize_accessors_in(*v, json[key.c_str()], remaining);
        if (remaining == 0) return remaining;
      }

      return remaining;
    }

    std::size_t deserialize_accessors_from(Context& ctx, const json::value& json, std::size_t remaining)
    {
      if (remaining == 0) return 0;
      for (const auto& [key, v] : ctx.accessors_of<persistance_service>()) {
        auto& acc = dynamic_cast<Persistant&>(*v);
        if (acc.provider() == this) {
          util::deserialize_from(json::get_or_null(json, acc.name()), acc);
          remaining--;
          if (remaining == 0) return 0;
        }
      }

      for (const auto& [key, v] : ctx.children()) {
        remaining = deserialize_accessors_from(*v, json::get_or_null(json, key.c_str()), remaining);
        if (remaining == 0) return 0;
      }
      return remaining;
    }
  };
} // namespace otto::itc
