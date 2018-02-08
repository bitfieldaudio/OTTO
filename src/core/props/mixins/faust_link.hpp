#pragma once

#include <vector>

#include "util/utility.hpp"

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

#include "has_value.hpp"

namespace otto::core::props::mixins {

  struct FaustLink {
    enum struct Type { ToFaust, FromFaust };

    FaustLink(const std::string_view& name,
              const std::function<float()>& get,
              float* faust_var)
      : name(name),
        type(Type::ToFaust),
        get_or_set_(get),
        faust_var_(faust_var)
    {}

    FaustLink(const std::string_view& name,
              const std::function<void(float)>& set,
              float* faust_var)
      : name(name),
        type(Type::FromFaust),
        get_or_set_(set),
        faust_var_(faust_var)
    {}

    void refresh()
    {
      if (type == Type::ToFaust) {
        *faust_var_ = mpark::get<0>(get_or_set_)();
      } else {
        mpark::get<1>(get_or_set_)(*faust_var_);
      }
    }

    void update(float& fptr)
    {
      if (type == Type::ToFaust) {
        *faust_var_ = fptr;
      } else {
        fptr = *faust_var_;
      }
    }

    const std::string_view name;
    Type const type;

  private:
    mpark::variant<std::function<float()>, std::function<void(float)>> const
      get_or_set_;
    float* const faust_var_;
  };

  OTTO_PROPS_MIXIN(faust_link, REQUIRES(faust_link, has_value));

  template<>
  struct mixin::leaf_interface<faust_link> {
    const std::function<void()> refresh_links;
  };

  template<>
  struct mixin::branch_interface<faust_link> : BaseBranchInterface<faust_link> {
    void refresh_links()
    {
      for (auto&& itf : children()) {
        if (itf.is_branch()) {
          itf.get_branch().refresh_links();
        } else {
          itf.get_leaf().refresh_links();
        }
      }
    }
  };

  OTTO_PROPS_MIXIN_IMPL(faust_link) {
    OTTO_PROPS_MIXIN_DECLS(faust_link);

    void refresh_links()
    {
      for (auto&& fl : faust_links_) {
        fl.refresh();
      }
    }

    void add_link(const FaustLink& fl)
    {
      faust_links_.push_back(fl);
    }

    void clear_links()
    {
      faust_links_.clear();
    }

    void on_hook(hook<has_value::hooks::on_set, HookOrder::After> & hook)
    {
      for (auto&& fl : faust_links_) {
        if (fl.type == FaustLink::Type::ToFaust) {
          fl.update(hook.value());
        }
      }
    }

    interface_type& interface() noexcept
    {
      return interface_;
    }

  private:
    std::vector<FaustLink> faust_links_;

    interface_type interface_ = {
      util::capture_this(&self_type::refresh_links, this)};
  };

} // namespace otto::core::props::mixins
