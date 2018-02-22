#pragma once

#include <json.hpp>

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

#include "services/logger.hpp"
#include "util/algorithm.hpp"
#include "util/exception.hpp"
#include "util/utility.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(serializable);

  template<>
  struct mixin::interface<serializable> {
    virtual void from_json(const nlohmann::json&) = 0;
    virtual nlohmann::json to_json() const             = 0;
    bool do_serialize;
  };

  OTTO_PROPS_MIXIN_BRANCH (serializable) {
    void from_json(const nlohmann::json& o) override
    {
      CHECK_F(o.is_object(), "Expected json object");
      for (auto it = o.begin(); it != o.end(); ++it) {
        auto found = util::find_if(children(), [key = it.key()](property_base& prop) {
            return prop.name() == key;
        });
        if (found != children().end()) {
          auto& item = static_cast<property_base&>(*found).as<serializable>();
          if (item.do_serialize) item.from_json(it.value());
        } else {
          throw util::exception("No property found matching {}", it.key());
        }
      }
    }

    nlohmann::json to_json() const override
    {
      auto js = nlohmann::json::object();
      for (property_base& itf : children()) {
        if (itf.as<serializable>().do_serialize)
          js[itf.name()] = itf.as<serializable>().to_json();
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
      return dynamic_cast<property_type const&>(*this).get();
    }

    void from_json(const nlohmann::json& js) override
    {
      dynamic_cast<property_type&>(*this).set(js);
    }
  };

} // namespace otto::core::props
