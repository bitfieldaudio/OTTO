#pragma once

#include <vector>
#include <string>
#include <functional>

namespace otto::core::props {

  /// Order of hook handlers.
  ///
  /// This is the second template argument to hook implementations, and is used
  /// to sort handlers.
  enum struct HookOrder {
    /// Should only read hook values
    Before,
    /// Change values early
    Early,
    /// Change values in the middle. Default
    Middle,
    /// Change values late
    Late,
    /// Should only read hook values
    After,
  };

  struct branch_base;

  namespace mixin {
    template<typename Tag>
    struct interface;
    template<typename Tag>
    struct branch;
  }

  /// Base class of all properties, leaves and branches both
  struct property_base {
    property_base(branch_base* parent = nullptr, std::string const& name = "");

    virtual ~property_base() = default;

    const std::string& name() const noexcept
    {
      return name_;
    }

    branch_base const* const parent() const noexcept
    {
      return parent_;
    }

    template<typename Tag>
    bool is() const noexcept
    {
      return dynamic_cast<mixin::interface<Tag> const*>(this);
    }

    template<typename Tag>
    mixin::interface<Tag>& as()
    {
      return dynamic_cast<mixin::interface<Tag>&>(*this);
    }

    template<typename Tag>
    mixin::interface<Tag> const& as() const
    {
      return dynamic_cast<mixin::interface<Tag> const&>(*this);
    }

    bool is_branch() const noexcept; 

    template<typename Tag>
    mixin::branch<Tag>& as_branch()
    {
      return dynamic_cast<mixin::branch<Tag>&>(*this);
    }

    template<typename Tag>
    mixin::branch<Tag> const& as_branch() const
    {
      return dynamic_cast<mixin::branch<Tag> const&>(*this);
    }

  private:
    branch_base* const parent_ = nullptr;
    std::string const name_ = "";
  };

  /// Base class of all property branches
  ///
  /// All mixin branches inherit virtually from this
  struct branch_base : property_base {

    using storage_type = std::vector<std::reference_wrapper<property_base>>;

    using property_base::property_base;

    branch_base() : property_base(nullptr, "") {}

    storage_type& children() {
      return storage_;
    }

    storage_type const& children() const {
      return storage_;
    }

    void push_back(property_base* ptr) {
      storage_.push_back(std::ref(*ptr));
    }

    void push_back(property_base& ref) {
      storage_.push_back(std::ref(ref));
    }

  private:
    storage_type storage_;
  };

  inline bool property_base::is_branch() const noexcept
  {
    return dynamic_cast<const branch_base*>(this);
  }

  /// Non-virtual base class for Properties
  ///
  /// Useful to get the adress of a common base class for branches, before the
  /// branch has been constructed. This is used in engines, where the base class
  /// AnyEngine is passed the adress of the engines `props` member, as a pointer
  /// to this type. At that point in construction `props` has not yet been
  /// constructed, so its v-table isn't set up, and it therefore cannot be
  /// converted to a virtual base class.
  struct properties_base : virtual branch_base {
    using branch_base::branch_base;
  };

} // namespace otto::core::props
