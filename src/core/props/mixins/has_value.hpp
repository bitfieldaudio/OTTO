#pragma once

#include "../internal/property.hpp"
#include "../internal/mixin_macros.hpp"

namespace otto::core::props::mixins {

  OTTO_PROPS_MIXIN( //
    has_value,
    // on_set can be used to modify the value before asignment,
    // as well as updating cached variables.
    HOOKS((on_set, value_type)),
    LEAF_INTERFACE({ const std::function<void()> reset; }))
  {
    OTTO_PROPS_MIXIN_DECLS(has_value);

    void init(const value_type& v)
    {
      set(v);
    }

    leaf_implementation() {}
    leaf_implementation(const value_type& v) : _value(v) {}

    const value_type& get() const
    {
      return _value;
    }

    void set(const value_type& v)
    {
      _value = run_hook<hooks::on_set>(v);
    }

    void reset(){};

    self_type& operator=(const value_type& rhs)
    {
      set(rhs);
      return *this;
    }

    operator const value_type&() const
    {
      return get();
    }

  protected:
    value_type _value;

    interface_type interface_ = {[this]() { reset(); }};
  };

}
