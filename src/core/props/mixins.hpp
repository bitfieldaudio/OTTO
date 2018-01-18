#pragma once

#include "base.hpp"
#include "macros.hpp"

#include <json.hpp>

namespace otto::core::props {

  namespace mixins {

    OTTO_PROPS_MIXIN(has_value)
    {
      OTTO_PROPS_MIXIN_DECLS(has_value);

      virtual value_type get() const
      {
        return value;
      }

      virtual void set(const value_type& v)
      {
        value = v;
      }

      self_type& operator=(const value_type& rhs)
      {
        value = rhs;
        return *this;
      }

      operator const value_type&() const
      {
        return value;
      }

      value_type value;
    };

    OTTO_PROPS_MIXIN(has_children)
    {
      OTTO_PROPS_MIXIN_DECLS(has_children);

      static_assert(
        std::is_void_v<value_type>,
        "A property that has children must have a value_type of void");

      static_assert(!is<has_value>,
                    "A property that has children must not have a value");
    };

    OTTO_PROPS_MIXIN(has_name)
    {
     OTTO_PROPS_MIXIN_DECLS(has_name);

      void init(std::string name)
      {
        _name = name;
      }

      const std::string& name()
      {
        return _name;
      }

    protected:
      std::string _name;
    };

    OTTO_PROPS_MIXIN(serializable, has_value)
    {
      OTTO_PROPS_MIXIN_DECLS(serializable);

      nlohmann::json to_json() const
      {
        if constexpr (is<has_children>) {
          return as<has_children>().children;
        } else {
          return as<has_value>().value;
        }
      }
    };

    OTTO_PROPS_MIXIN(faust_link)
    {
      OTTO_PROPS_MIXIN_DECLS(faust_link);

      void update_link();
      void add_link();
    };

    OTTO_PROPS_MIXIN(with_cache)
    {
      OTTO_PROPS_MIXIN_DECLS(with_cache);

      void update_cache();
      value_type cached_value();
    };

    OTTO_PROPS_MIXIN(steppable, has_value)
    {
      OTTO_PROPS_MIXIN_DECLS(steppable);

      void init(value_type p_step_size = value_type{1})
      {
        step_size = p_step_size;
      }

      void step(int n)
      {
        as<has_value>().set(as<has_value>().get() + n * step_size);
      }

      value_type step_size;
    };

  } // namespace mixins

} // namespace otto::core::props
