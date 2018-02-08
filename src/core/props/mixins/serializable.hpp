#pragma once

#include <json.hpp>

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

#include "has_name.hpp"
#include "has_value.hpp"

namespace otto::core::props::mixins {

  OTTO_PROPS_MIXIN(serializable, REQUIRES(has_value, has_name));

  template<>
  struct mixin::leaf_interface<serializable> {
    const std::string& name;
    std::function<void(const nlohmann::json&)> from_json;
    std::function<nlohmann::json()> to_json;
  };

  OTTO_PROPS_MIXIN_IMPL(serializable)
  {
    OTTO_PROPS_MIXIN_DECLS(serializable);

    nlohmann::json to_json() const
    {
      return as<has_value>().get();
    }

    void from_json(const nlohmann::json& js)
    {
      as<has_value>().set(js);
    }

    interface_type& interface()
    {
      return interface_;
    }

  private:
    interface_type interface_ = {
      as<has_name>().name(),
      [this](const nlohmann::json& js) { from_json(js); },
      [this]() -> nlohmann::json { return to_json(); }};
  };

  template<>
  struct mixin::branch_interface<serializable>
    : BaseBranchInterface<serializable> {
    void from_json(const nlohmann::json& js) {}

    nlohmann::json to_json()
    {
      auto js = nlohmann::json::object();
      for (auto& itf : children()) {
        if (itf.is_branch()) {
          js[itf.get_branch().name()] = itf.get_branch().to_json();
        } else {
          js[itf.get_leaf().name] = itf.get_leaf().to_json();
        }
      }
      return js;
    }
  };
} // namespace otto::core::props::mixins
