#pragma once

#include <vector>

#include "util/utility.hpp"

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

#include "services/logger.hpp"
#include "util/algorithm.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(faust_link);

  struct FaustLink {
    float* const faust_var_;
    enum struct Type { ToFaust, FromFaust } const type;
  };

  OTTO_PROPS_MIXIN_INTERFACE (faust_link) {
    virtual void refresh_links()          = 0;
    virtual void register_link(std::vector<std::string>::const_iterator first,
                               std::vector<std::string>::const_iterator last,
                               FaustLink) = 0;
    virtual void clear() = 0;
  };

  OTTO_PROPS_MIXIN_BRANCH (faust_link) {
    void refresh_links() override
    {
      for (property_base& itf : children()) {
        if (itf.is<faust_link>()) itf.as<faust_link>().refresh_links();
      }
    }

    void register_link(std::vector<std::string>::const_iterator first,
                       std::vector<std::string>::const_iterator last,
                       FaustLink link) override
    {
      auto found = util::find_if(
        children(),
        [& name = *first](auto&& child) { return child.get().name() == name; });
      if (found != children().end()) {
        auto& item = static_cast<property_base&>(*found);
        item.as<faust_link>().register_link(std::move(++first), std::move(last),
                                            link);
      } else {
        LOGW("Developer warning: Attempt to register a faust link for {} failed", *first);
      }
    }

    void clear() override {
      for (property_base& itf : children()) {
        if (itf.is<faust_link>()) itf.as<faust_link>().clear();
      }
    }
  };

  OTTO_PROPS_MIXIN_LEAF (faust_link) {
    OTTO_PROPS_MIXIN_DECLS(faust_link);

    void init(FaustLink::Type type)
    {
      type_ = type;
    }

    void refresh_links() override
    {
      auto& value = dynamic_cast<property_type*>(this)->get();
      if (type_ == FaustLink::Type::ToFaust) {
        for (auto&& fl : faust_links_) {
          *fl = value;
        }
      } else {
        for (auto&& fl : faust_links_) {
          dynamic_cast<property_type*>(this)->set(*fl);
        }
      }
    }

    void add_link(const FaustLink& fl)
    {
      faust_links_.push_back(fl.faust_var_);
    }

    void register_link(std::vector<std::string>::const_iterator first,
                       std::vector<std::string>::const_iterator last,
                       FaustLink link) override
    {
      add_link(std::move(link));
    }

    void clear() override
    {
      faust_links_.clear();
    }

    void on_hook(hook<common::hooks::on_set, HookOrder::After> & hook)
    {
      if (type_ == FaustLink::Type::ToFaust) {
        for (auto&& fl : faust_links_) {
          *fl = hook.value();
        }
      }
    }

    const FaustLink::Type& type = type_;

  private:
    FaustLink::Type type_ = FaustLink::Type::ToFaust;
    std::vector<float*> faust_links_;
  };

} // namespace otto::core::props
