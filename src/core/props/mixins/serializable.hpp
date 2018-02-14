#pragma once

#include <json.hpp>

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

#include "services/logger.hpp"
#include "util/algorithm.hpp"
#include "util/exception.hpp"
#include "util/utility.hpp"

#include "has_name.hpp"
#include "has_value.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(serializable, REQUIRES(has_value, has_name));

  template<>
  struct mixin::leaf_interface<serializable> {
    const std::string& name;
    std::function<void(const nlohmann::json&)> from_json;
    std::function<nlohmann::json()> to_json;
    const bool& do_serialize;
  };

  template<>
  struct mixin::branch_interface<serializable>
    : BaseBranchInterface<serializable> {
    void from_json(const nlohmann::json& o)
    {
      CHECK_F(o.is_object(), "Expected json object");
      for (auto it = o.begin(); it != o.end(); ++it) {
        auto found = util::find(children(), [key = it.key()](auto itf) {
          if (itf.is_leaf()) return itf.get_leaf().name == key;
          if (itf.is_branch()) return itf.get_branch().name() == key;
        });
        if (found != children().end()) {
          if (found->is_leaf()) {
            if (found->get_leaf().do_serialize)
              found->get_leaf().from_json(it.value());
          }
          if (found->is_branch()) found->get_branch().from_json(it.value());
        } else {
          throw util::exception("No property found matching {}", it.key());
        }
      }
    }

    nlohmann::json to_json()
    {
      auto js = nlohmann::json::object();
      for (auto& itf : children()) {
        if (itf.is_branch()) {
          js[itf.get_branch().name()] = itf.get_branch().to_json();
        } else {
          auto& leaf = itf.get_leaf();
          if (leaf.do_serialize) js[leaf.name] = leaf.to_json();
        }
      }
      return js;
    }
  };

  OTTO_PROPS_MIXIN_IMPL(serializable)
  {
    OTTO_PROPS_MIXIN_DECLS(serializable);

    void init(bool do_serialize)
    {
      this->do_serialize = do_serialize;
    }

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

    bool do_serialize;

  private:
    interface_type interface_ = {
      as<has_name>().name(),
      [this](const nlohmann::json& js) { from_json(js); },
      [this]() -> nlohmann::json { return to_json(); }, do_serialize};
  };

} // namespace otto::core::props::mixins
