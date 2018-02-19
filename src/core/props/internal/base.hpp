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

  struct properties_base;

  namespace mixin {
    template<typename Tag>
    struct interface;
  }

  /// Base class of all properties, leaves and branches both
  struct property_base {
    property_base(properties_base* parent, std::string const& name)
      : parent_(parent), name_(name)
    {}

    virtual ~property_base() = default;

    const std::string& name() const noexcept
    {
      return name_;
    }

    properties_base const* const parent() const noexcept
    {
      return parent_;
    }

    template<typename Tag>
    bool is() const noexcept
    {
      return dynamic_cast<mixin::interface<Tag>*>(this);
    }

    template<typename Tag>
    mixin::interface<Tag>& as()
    {
      return dynamic_cast<mixin::interface<Tag>&>(this);
    }

    template<typename Tag>
    mixin::interface<Tag> const& as() const
    {
      return dynamic_cast<mixin::interface<Tag>&>(this);
    }

    bool is_branch() const noexcept; 

  private:
    properties_base* const parent_ = nullptr;
    std::string const name_ = "";
  };

  /// Base class of all property branches
  struct properties_base : virtual property_base {

    using storage_type = std::vector<std::reference_wrapper<property_base>>;

    storage_type& children() {
      return storage_;
    }

    void push_back(property_base* ptr) {
      storage_.push_back(std::ref(*ptr));
    }

  private:
    storage_type storage_;
  };

  bool property_base::is_branch() const noexcept
  {
    return dynamic_cast<const properties_base*>(this);
  }

} // namespace otto::core::props
