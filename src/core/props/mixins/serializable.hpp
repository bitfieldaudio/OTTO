#pragma once

#include <json.hpp>

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

#include "services/logger.hpp"
#include "util/algorithm.hpp"
#include "util/exception.hpp"
#include "util/utility.hpp"

namespace otto::core::props {

  namespace detail {
    template<typename T>
    struct is_array : std::false_type {};

    template<typename T, std::size_t N>
    struct is_array<std::array<T, N>> : std::true_type {
      static constexpr std::size_t size = N;
    };

  } // namespace detail

  OTTO_PROPS_MIXIN(serializable);

  template<>
  struct mixin::interface<serializable> {
    virtual void from_json(const nlohmann::json&) = 0;
    virtual nlohmann::json to_json() const = 0;
    bool do_serialize = true;
  };

  OTTO_PROPS_MIXIN_BRANCH (serializable) {
    void from_json(const nlohmann::json& o) override
    {
      CHECK_F(o.is_object(), "Expected json object");
      for (auto it = o.begin(); it != o.end(); ++it) {
        auto found = util::find_if(
          children(), [key = it.key()](property_base& prop) { return prop.name() == key; });
        if (found != children().end()) {
          auto& prop = static_cast<property_base&>(*found);
          if (prop.is<serializable>()) {
            auto& item = prop.as<serializable>();
            if (item.do_serialize) item.from_json(it.value());
          }
        } else {
          throw util::exception("No property found matching {}", it.key());
        }
      }
    }

    nlohmann::json to_json() const override
    {
      auto js = nlohmann::json::object();
      for (property_base& prop : children()) {
        if (prop.is<serializable>()) {
          if (prop.as<serializable>().do_serialize)
            js[prop.name()] = prop.as<serializable>().to_json();
        }
      }
      return js;
    }
  };

  OTTO_PROPS_MIXIN_LEAF (serializable) {
    OTTO_PROPS_MIXIN_DECLS(serializable);

    void init(bool do_serialize)
    {
      this->do_serialize = do_serialize;
    }

    nlohmann::json to_json() const override
    {
      // Unwrap enums
      return util::underlying(dynamic_cast<property_type const&>(*this).get());
    }

    void from_json(const nlohmann::json& js) override
    {
      if constexpr (std::is_enum_v<value_type>) {
        dynamic_cast<property_type&>(*this).set(
          static_cast<value_type>(static_cast<std::underlying_type_t<value_type>>(js)));
      } else if constexpr (detail::is_array<value_type>::value) {
        std::vector<typename value_type::value_type> vec = js;
        if (vec.size() == std::tuple_size_v<value_type>) {
          value_type array;
          util::copy(vec, array.begin());
          dynamic_cast<property_type&>(*this).set(std::move(array));
        } else {
          throw util::exception("Array had wront size");
        }
      } else {
        dynamic_cast<property_type&>(*this).set(js);
      }
    }
  };

} // namespace otto::core::props
